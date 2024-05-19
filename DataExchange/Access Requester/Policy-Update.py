from cryptography.fernet import Fernet
import json
import PyPDF2
import subprocess
import os
import tempfile
import base64
import random
import timeit
from google.cloud import storage

# Define paths
oldkey_path = "/home/phukaokk/SIIT Project/HDIMS/DataExchange/Data_Owner"
cpabe_path = "/home/phukaokk/SIIT Project/HDIMS/DataExchange/cpabe-0.11"
base_path = "/home/phukaokk/SIIT Project/HDIMS/DataExchange/Access_Requester"
pub_key_path = os.path.join(oldkey_path, "pub_key")
master_key_path = os.path.join(oldkey_path, "master_key")
priv_key_dir = os.path.join(base_path, "cpabe_keys")

# Download data.json from GCS before processing
bucket_name = "hospital-a"
object_name = "proxy-test.json"
local_data_path = "proxy-test.json"

def download_data_from_gcs(bucket_name, object_name, local_file_path):
    """Downloads a file from Google Cloud Storage."""
    client = storage.Client()
    bucket = client.bucket(bucket_name)
    blob = bucket.blob(object_name)
    blob.download_to_filename(local_file_path)

def decrypt_file(encrypted_content_base64, key):
    f = Fernet(key)
    encrypted_content = base64.b64decode(encrypted_content_base64.encode())
    decrypted_content = f.decrypt(encrypted_content)
    with tempfile.NamedTemporaryFile(delete=False, suffix=".pdf") as file:
        file.write(decrypted_content)
        file.flush()
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

def decrypt_key(encrypted_key_base64, priv_key_name):
    cpabe_dec_path = os.path.join(cpabe_path, 'cpabe-dec')
    encrypted_key_path = os.path.join(priv_key_dir, "encrypted_key.cpabe")
    with open(encrypted_key_path, "wb") as f:
        f.write(base64.b64decode(encrypted_key_base64))
    decrypted_key_path = os.path.join(base_path, "decrypted_key")
    priv_key_path = os.path.join(priv_key_dir, priv_key_name)
    subprocess.run([cpabe_dec_path, pub_key_path, priv_key_path, encrypted_key_path, '-o', decrypted_key_path], check=True)
    with open(decrypted_key_path, "rb") as f:
        decrypted_key = f.read()
    return decrypted_key

def encrypt_key(key, policy):
    with tempfile.NamedTemporaryFile(delete=False) as temp_key_file:
        temp_key_file.write(key)
        temp_key_file.flush()
        cpabe_enc_path = os.path.join(cpabe_path, 'cpabe-enc')
        encrypted_key_path = os.path.join(priv_key_dir, "reencrypted_key.cpabe")
        subprocess.run([cpabe_enc_path, '-k', pub_key_path, temp_key_file.name, policy, '-o', encrypted_key_path], check=True)
    with open(encrypted_key_path, "rb") as f:
        encrypted_key = base64.b64encode(f.read()).decode("utf-8")
    return encrypted_key

def main():
    download_data_from_gcs(bucket_name, object_name, local_data_path)

    # Load the symmetric key and encrypted file from the downloaded data.json
    with open(local_data_path, "r") as file:
        data = json.load(file)

    # Define the attributes required for decryption
    attributes = ['developer', 'it_department']

    # Generate the private key for the attributes
    priv_name = 'AR_priv'
    generate_private_key(attributes, priv_name)

    decryption_times = []
    reencryption_times = []

    for index, entry in enumerate(data[:10]):  # Start with processing 10 entries for the test
        encrypted_content_base64 = entry["files"][0]["CT_1"]
        encrypted_key_base64 = entry["files"][0]["CT_2"]

        # Decrypt the symmetric key using CP-ABE
        start_time = timeit.default_timer()
        decrypted_key = decrypt_key(encrypted_key_base64, priv_name)
        stop_time = timeit.default_timer()
        decryption_time = stop_time - start_time
        decryption_times.append(decryption_time)

        # Decrypt the PDF file
        decrypted_file_path = decrypt_file(encrypted_content_base64, decrypted_key)

        # Save the decrypted PDF file to the local machine
        with open(decrypted_file_path, "rb") as file:
            with open(f"decrypted_{index}.pdf", "wb") as decrypted:
                decrypted.write(file.read())

        # Open the decrypted PDF file
        with open(f"decrypted_{index}.pdf", "rb") as file:
            pdf_reader = PyPDF2.PdfReader(file)
            print(f"PDF {index} metadata:", pdf_reader.metadata)

        # Re-encrypt the symmetric key with a new random policy
        new_policy = f"({random.choice(['admin', 'user'])} and it_department) or (developer and {random.choice(['finance', 'hr'])})"
        start_reenc_time = timeit.default_timer()
        re_encrypted_key = encrypt_key(decrypted_key, new_policy)
        stop_reenc_time = timeit.default_timer()
        reenc_time = stop_reenc_time - start_reenc_time
        reencryption_times.append(reenc_time)

        # Decrypt the re-encrypted symmetric key to verify the process
        new_priv_name = 'AR_repriv'
        new_attributes = ['admin', 'it_department']
        generate_private_key(new_attributes, new_priv_name)
        start_redec_time = timeit.default_timer()
        decrypted_reencrypted_key = decrypt_key(re_encrypted_key, new_priv_name)
        stop_redec_time = timeit.default_timer()
        redecryption_time = stop_redec_time - start_redec_time

        # Verify the re-encryption process
        assert decrypted_key == decrypted_reencrypted_key, f"Re-encryption process failed for index {index}. Keys do not match."

        print(f"Re-encryption Time for index {index}: {reenc_time} seconds")
        print(f"Re-decryption Time for index {index}: {redecryption_time} seconds")

    print(f"Average Decryption Time: {sum(decryption_times) / len(decryption_times)} seconds")
    print(f"Average Re-encryption Time: {sum(reencryption_times) / len(reencryption_times)} seconds")

if __name__ == "__main__":
    main()
