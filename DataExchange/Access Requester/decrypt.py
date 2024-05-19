from cryptography.fernet import Fernet
import json
import PyPDF2
import subprocess
import os
import tempfile
import base64

def download_data_from_gcs(bucket_name, object_name, local_file_path):
  """Downloads a file from Google Cloud Storage.

  Args:
      bucket_name: The name of the bucket containing the file.
      object_name: The name of the file to download.
      local_file_path: The path to save the downloaded file locally.
  """
  # Import the Google Cloud Storage library (assuming it's not already imported)
  from google.cloud import storage

  # Create a storage client
  client = storage.Client()

  # Get a reference to the bucket
  bucket = client.bucket(bucket_name)

  # Get a reference to the object (file)
  blob = bucket.blob(object_name)

  # Download the object to the local file
  blob.download_to_filename(local_file_path)
  
def decrypt_file(encrypted_file_path, key):

    f = Fernet(key)
    # Decode the base64-encoded encrypted contents to bytes
    encrypted_content = base64.b64decode(encrypted_content_base64.encode())

    # Decrypt the contents
    decrypted_content = f.decrypt(encrypted_content)

    # Create a temporary file to write the decrypted contents
    with tempfile.NamedTemporaryFile(delete=False, suffix=".pdf") as file:
        file.write(decrypted_content)
        file.flush()


        # Open the temporary file and return the file path
        return file.name

def generate_private_key(attributes, priv_name):

    # Run the cpabe-keygen command in the Docker container
    try:
        subprocess.run(["docker", "exec", "cp-abe", "cpabe-keygen", "-o", priv_name, "pub_key", "master_key", attributes[0], attributes[1]])

        # Copy the private key file from the Docker container to the host machine
        private_key_path = os.path.join(cpabe_keys_dir, priv_name)
        subprocess.run(["docker", "cp", f"{container_id}:/root/{priv_name}", private_key_path])

        # Read the private key from the file
        with open(private_key_path, "rb") as f:
            private_key = f.read()

    except subprocess.CalledProcessError as e:
        print(f"Error running cpabe-keygen: {e.stderr.decode()}")

        private_key = None

    return private_key

def decrypt_key(encrypted_key_path, priv_name):
    # Copy the encrypted key file from the host machine to the Docker container
    encrypted_key_name = os.path.basename(encrypted_key_path)
    subprocess.run(["docker", "cp", encrypted_key_path, f"{container_id}:/root/encrypted_key.cpabe"])

    # Run the cpabe-keygen command in the Docker container
    try:
        subprocess.run(["docker", "exec", "cp-abe", "cpabe-dec", "pub_key", priv_name, "encrypted_key.cpabe"])

        # Copy the private key file from the Docker container to the host machine
        decrypted_key_path = os.path.join(cpabe_keys_dir, "decrypted_key")
        subprocess.run(["docker", "cp", f"{container_id}:/root/encrypted_key", decrypted_key_path])

        # Read the decrypted key from the file
        with open(decrypted_key_path, "rb") as f:
            decrypted_key = f.read()

    except subprocess.CalledProcessError as e:
        print(f"Error running cpabe-keygen: {e.stderr.decode()}")

        decrypted_key = None

    return decrypted_key

python_file_path = os.path.abspath(__file__)
cpabe_keys_dir = os.path.join(os.path.dirname(python_file_path), "cpabe_keys")
container_id = subprocess.run(["docker", "ps", "-q"], capture_output=True, text=True).stdout.strip()

# Download data.json from GCS before processing
bucket_name = "hospital-a"  # Replace with your bucket name
object_name = "data.json"
local_data_path = "data.json"  # Path to save downloaded data.json locally

download_data_from_gcs(bucket_name, object_name, local_data_path)

# Load the symmetric key and encrypted file from the downloaded data.json
with open(local_data_path, "r") as file:
    data = json.load(file)

# Define the attributes required for decryption
attributes= ['developer' , 'it_department']

# Generate the private key for the attributes
priv_name = 'AR_priv'
private_key = generate_private_key(attributes, priv_name)

encrypted_content_base64 = data["files"][0]["CT_1"]
encrypted_key_path = data["files"][0]["CT_2"]
key = decrypt_key(encrypted_key_path, priv_name)
print("AES key: ", key)

# Decrypt the PDF file
decrypted_file_path = decrypt_file(encrypted_content_base64, key.decode())

# Save the decrypted PDF file to the local machine
with open(decrypted_file_path, "rb") as file:
    with open("decrypted.pdf", "wb") as decrypted:
        decrypted.write(file.read())

# Open the decrypted PDF file
with open("decrypted.pdf", "rb") as file:
    pdf_reader = PyPDF2.PdfReader(file)
    print(pdf_reader.metadata)