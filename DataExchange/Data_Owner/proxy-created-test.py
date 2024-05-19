import subprocess
import os
import json
import tempfile
import base64
from cryptography.fernet import Fernet
from google.cloud import storage
import timeit

# Define paths
base_path = "/home/phukaokk/SIIT Project/HDIMS/DataExchange/Data_Owner"
pub_key_path = os.path.join(base_path, "pub_key")
master_key_path = os.path.join(base_path, "master_key")
priv_key_dir = os.path.join(base_path, "cpabe_keys")
cpabe_path = "/home/phukaokk/SIIT Project/HDIMS/DataExchange/cpabe-0.11"

# Function to generate a symmetric key
def generate_key():
    return Fernet.generate_key()

# Function to encrypt a file using AES symmetric encryption
def encrypt_file(file_path, key):
    f = Fernet(key)
    with open(file_path, "rb") as file:
        file_content = file.read()
    encrypted_content = f.encrypt(file_content)
    return base64.b64encode(encrypted_content).decode()

# Function to generate the public key and master key using cpabe-setup
def setup_cpabe():
    cpabe_setup_path = os.path.join(cpabe_path, 'cpabe-setup')
    subprocess.run([cpabe_setup_path], check=True)

# Function to generate the private key using cpabe-keygen
def generate_private_key(attributes, priv_name):
    priv_key_path = os.path.join(priv_key_dir, priv_name)
    cpabe_keygen_path = os.path.join(cpabe_path, 'cpabe-keygen')
    subprocess.run([cpabe_keygen_path, '-o', priv_key_path, pub_key_path, master_key_path] + attributes, check=True)
    with open(priv_key_path, "rb") as f:
        private_key = base64.b64encode(f.read()).decode("utf-8")
    return private_key

# Function to encrypt the symmetric key using cpabe-enc
def encrypt_key(key, policy, priv_name):
    if isinstance(key, list) and len(key) == 1:
        key = key[0]
    with tempfile.NamedTemporaryFile(delete=False) as temp_key_file:
        temp_key_file.write(key.encode())
        temp_key_file.flush()
        cpabe_enc_path = os.path.join(cpabe_path, 'cpabe-enc')
        encrypted_key_filename = priv_name + ".cpabe"
        encrypted_key_path = os.path.join(priv_key_dir, encrypted_key_filename)
        subprocess.run([cpabe_enc_path, '-k', pub_key_path, temp_key_file.name, policy, '-o', encrypted_key_path], check=True)
        os.remove(temp_key_file.name)
    with open(encrypted_key_path, "rb") as f:
        encrypted_key = base64.b64encode(f.read()).decode("utf-8")
    return encrypted_key

# Function to upload a file to Google Cloud Storage
def upload_to_gcs(bucket_name, source_file_path, destination_blob_name):
    client = storage.Client()
    bucket = client.bucket(bucket_name)
    blob = bucket.blob(destination_blob_name)
    blob.upload_from_filename(source_file_path)
    print(f"File {source_file_path} uploaded to {bucket_name}/{destination_blob_name}")

# Encrypt a PDF file and save the symmetric key in a JSON file
pdf_file_path = "EHR_Template.pdf"
start_DO_time = timeit.default_timer()
key = generate_key()
encrypted_content = encrypt_file(pdf_file_path, key)

# Generate the public key and master key using cpabe-setup
setup_cpabe()

# Initialize a list to hold all data entries
data_entries = []

for i in range(1, 21):
    attributes = ['admin', 'it_department']
    priv_name = f'DO_priv_{i}'
    private_key = generate_private_key(attributes, priv_name)
    policy = "(admin and it_department) or (developer and it_department)"
    encrypted_key = encrypt_key(key.decode(), policy, priv_name)
    file_data = {
        "ID": i,
        "CT_1": encrypted_content,
        "CT_2": encrypted_key
    }
    data_entry = {
        "DID": f"00{i:02d}",
        "files": [file_data]
    }
    data_entries.append(data_entry)

with open("proxy-test.json", "w") as file:
    json.dump(data_entries, file, indent=4)

bucket_name = "hospital-a"
upload_to_gcs(bucket_name, "proxy-test.json", "proxy-test.json")

stop_DO_time = timeit.default_timer()
sym_time = stop_DO_time - start_DO_time
print("Data Owner storing file Time: " + str(sym_time))
