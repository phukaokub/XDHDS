import subprocess
import os
import json
import tempfile
import base64
from cryptography.fernet import Fernet
from google.cloud import storage

# Define paths
base_path = "/home/phukaokk/SIIT Project/HDIMS/DataExchange/Data_Owner"
pub_key_path = os.path.join(base_path, "pub_key")
master_key_path = os.path.join(base_path, "master_key")
# symkey_dir = os.path.join(base_path, "Symkeys")
priv_key_dir = os.path.join(base_path, "cpabe_keys")
cpabe_path = "/home/phukaokk/SIIT Project/HDIMS/DataExchange/cpabe-0.11"

# Function to generate a symmetric key
def generate_key():
    return Fernet.generate_key()

# Function to encrypt a file using AES symmetric encryption
def encrypt_file(file_path, key):
    f = Fernet(key)

    # Read the contents of the file
    with open(file_path, "rb") as file:
        file_content = file.read()

    # Encrypt the contents
    encrypted_content = f.encrypt(file_content)

    # Convert the encrypted content to a base64-encoded string
    base64_encoded_content = base64.b64encode(encrypted_content)

    # Return the base64-encoded encrypted content
    return base64_encoded_content.decode()

# Function to generate the public key and master key using cpabe-setup
def setup_cpabe():
    cpabe_setup_path = os.path.join(cpabe_path, 'cpabe-setup')
    subprocess.run([cpabe_setup_path], check=True)

# Function to generate the private key using cpabe-keygen
def generate_private_key(attributes, priv_name):
    priv_key_path = os.path.join(priv_key_dir, priv_name)
    cpabe_keygen_path = os.path.join(cpabe_path, 'cpabe-keygen')
    subprocess.run([cpabe_keygen_path, '-o', priv_key_path, pub_key_path, master_key_path] + attributes, check=True)

    # Read the private key from the file
    with open(priv_key_path, "rb") as f:
        private_key = base64.b64encode(f.read()).decode("utf-8")

    return private_key

# Function to encrypt the symmetric key using cpabe-enc
def encrypt_key(key, policy):
    if isinstance(key, list) and len(key) == 1:
        key = key[0]

    # Write the symmetric key to a temporary file
    with tempfile.NamedTemporaryFile(delete=False) as temp_key_file:
        temp_key_file.write(key.encode())
        temp_key_file.flush()

        cpabe_enc_path = os.path.join(cpabe_path, 'cpabe-enc')
        encrypted_key_filename = "encrypted_key.cpabe"
        encrypted_key_path = os.path.join(priv_key_dir, encrypted_key_filename)
        subprocess.run([cpabe_enc_path, '-k', pub_key_path, temp_key_file.name, policy, '-o', encrypted_key_path], check=True)

        # Remove the temporary file
        os.remove(temp_key_file.name)

    return encrypted_key_path

# Function to upload a file to Google Cloud Storage
def upload_to_gcs(bucket_name, source_file_path, destination_blob_name):
    """Uploads a file to a Google Cloud Storage bucket.

    Args:
        bucket_name: The name of the bucket to upload the file to.
        source_file_path: The local path of the file to upload.
        destination_blob_name: The name of the object (file) in the bucket.
    """

    # Create a storage client
    client = storage.Client()

    # Get a reference to the bucket
    bucket = client.bucket(bucket_name)

    # Create a blob object representing the destination file
    blob = bucket.blob(destination_blob_name)

    # Upload the file to the bucket
    blob.upload_from_filename(source_file_path)

    print(f"File {source_file_path} uploaded to {bucket_name}/{destination_blob_name}")

# Encrypt a PDF file and save the symmetric key in a JSON file
pdf_file_path = "EHR_Template.pdf"
key = generate_key()
print("AES key: ", key.decode())
encrypted_content = encrypt_file(pdf_file_path, key)

# Generate the public key and master key using cpabe-setup
setup_cpabe()

# Define the attributes required for decryption
attributes = ['sysadmin', 'it_department']
priv_name = 'DO_priv'

# Generate the private key for the attributes
private_key = generate_private_key(attributes, priv_name)

# Encrypt the symmetric key using CP-ABE
policy = "(sysadmin and it_department) or (developer and it_department)"
encrypted_key = encrypt_key(key.decode(), policy)

# Create a dictionary to store the encrypted file and the symmetric key
data = {
    "DID": "001",
    "files": []
}

file_data = {
    "ID": 1,
    "CT_1": encrypted_content,
    "CT_2": encrypted_key
}

data["files"].append(file_data)

# Save the dictionary in a JSON file
with open("data.json", "w") as file:
    json.dump(data, file)

# Upload data.json to Google Cloud Storage
bucket_name = "hospital-a"
upload_to_gcs(bucket_name, "data.json", "data.json")