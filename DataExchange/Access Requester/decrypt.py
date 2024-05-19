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
    encrypted_content = base64.b64decode(encrypted_file_path.encode())

    # Decrypt the contents
    decrypted_content = f.decrypt(encrypted_content)

    # Create a temporary file to write the decrypted contents
    with tempfile.NamedTemporaryFile(delete=False, suffix=".pdf") as file:
        file.write(decrypted_content)
        file.flush()

        # Open the temporary file and return the file path
        return file.name

# Function to generate the private key using cpabe-keygen
def generate_private_key(attributes, priv_name):
    priv_key_path = os.path.join(priv_key_dir, priv_name)
    cpabe_keygen_path = os.path.join(cpabe_path, 'cpabe-keygen')
    subprocess.run([cpabe_keygen_path, '-o', priv_key_path, pub_key_path, master_key_path] + attributes, check=True)

    # Read the private key from the file
    with open(priv_key_path, "rb") as f:
        private_key = base64.b64encode(f.read()).decode("utf-8")

    return private_key

def decrypt_key(encrypted_key_path, priv_key_name, cpabe_path, pub_key_path):
    cpabe_dec_path = os.path.join(cpabe_path, 'cpabe-dec')
    decrypted_key_path = os.path.join(base_path, "decrypted_key")
    priv_key_path = os.path.join(priv_key_dir, priv_key_name)
    subprocess.run([cpabe_dec_path, pub_key_path, priv_key_path, encrypted_key_path, '-o', decrypted_key_path], check=True)

    # Read the decrypted key from the file
    with open(decrypted_key_path, "rb") as f:
        decrypted_key = f.read()

    return decrypted_key

# Define paths
oldkey_path = "/home/phukaokk/SIIT Project/HDIMS/DataExchange/Data_Owner"
cpabe_path = "/home/phukaokk/SIIT Project/HDIMS/DataExchange/cpabe-0.11"
base_path = "/home/phukaokk/SIIT Project/HDIMS/DataExchange/Access Requester"
pub_key_path = os.path.join(oldkey_path, "pub_key")
master_key_path = os.path.join(oldkey_path, "master_key")
priv_key_dir = os.path.join(base_path, "cpabe_keys")

# Download data.json from GCS before processing
bucket_name = "hospital-a"  # Replace with your bucket name
object_name = "data.json"
local_data_path = "data.json"  # Path to save downloaded data.json locally

download_data_from_gcs(bucket_name, object_name, local_data_path)

# Load the symmetric key and encrypted file from the downloaded data.json
with open(local_data_path, "r") as file:
    data = json.load(file)

# Define the attributes required for decryption
attributes = ['developer', 'it_department']

# Generate the private key for the attributes
priv_name = 'AR_priv'
private_key = generate_private_key(attributes, priv_name)

encrypted_content_base64 = data["files"][0]["CT_1"]
encrypted_key_path = data["files"][0]["CT_2"]
print(encrypted_key_path)
decrypted_key = decrypt_key(encrypted_key_path, priv_name, cpabe_path, pub_key_path)
key = decrypted_key
print("AES key: ", key)

# Decrypt the PDF file
decrypted_file_path = decrypt_file(encrypted_content_base64, key)

# Save the decrypted PDF file to the local machine
with open(decrypted_file_path, "rb") as file:
    with open("decrypted.pdf", "wb") as decrypted:
        decrypted.write(file.read())

# Open the decrypted PDF file
with open("decrypted.pdf", "rb") as file:
    pdf_reader = PyPDF2.PdfReader(file)
    print(pdf_reader.metadata)