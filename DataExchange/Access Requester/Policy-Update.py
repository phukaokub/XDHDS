import json
import subprocess
import time
import os
import tempfile
from statistics import mean
from operator import xor
from cryptography.fernet import Fernet
import random
import string
import os, subprocess,timeit, time, base64



# Define paths
oldkey_path = "/home/phukaokk/SIIT Project/HDIMS/DataExchange/Data_Owner"
cpabe_path = "/home/phukaokk/SIIT Project/HDIMS/DataExchange/cpabe-0.11"
base_path = "/home/phukaokk/SIIT Project/HDIMS/DataExchange/Access Requester"
pub_key_path = os.path.join(oldkey_path, "pub_key")
master_key_path = os.path.join(oldkey_path, "master_key")
priv_key_dir = os.path.join(base_path, "cpabe_keys")

# Function to decrypt the key using cpabe-dec
def decrypt_key(encrypted_key_path, old_policy):
    priv_key_path = os.path.join(priv_key_dir, f"proxy_priv_{old_policy}")
    cpabe_keygen_path = os.path.join(cpabe_path, 'cpabe-keygen')
    subprocess.run([cpabe_keygen_path, '-o', priv_key_path, pub_key_path, master_key_path, old_policy], check=True)

    cpabe_dec_path = os.path.join(cpabe_path, 'cpabe-dec')
    decrypted_key_path = os.path.join(cpabe_path, "decrypted_key")
    subprocess.run([cpabe_dec_path, '-k', pub_key_path, priv_key_path, encrypted_key_path, '-o', decrypted_key_path], check=True)

    # Read the decrypted key from the file
    with open(decrypted_key_path, "rb") as f:
        decrypted_key = f.read()

    return decrypted_key
 
def encrypt_key(key, policy):
    cpabe_enc_path = os.path.join(cpabe_path, 'cpabe-enc')
    encrypted_key_path = os.path.join(priv_key_dir, f"encrypted_key_{policy}.cpabe")
    subprocess.run([cpabe_enc_path, '-k', pub_key_path, key, policy, '-o', encrypted_key_path], check=True)

    return encrypted_key_path

# Function to re-encrypt the key using cpabe-enc
def re_encrypt_key(decrypted_key, new_policy):
    # Write the decrypted key to a temporary file
    with tempfile.NamedTemporaryFile(delete=False) as temp_key_file:
        temp_key_file.write(decrypted_key)
        temp_key_file.flush()

        cpabe_enc_path = os.path.join(cpabe_path, 'cpabe-enc')
        re_encrypted_key_path = os.path.join(priv_key_dir, f"re_encrypted_key_{new_policy}.cpabe")
        subprocess.run([cpabe_enc_path, '-k', pub_key_path, temp_key_file.name, new_policy, '-o', re_encrypted_key_path], check=True)

        # Remove the temporary file
        os.remove(temp_key_file.name)

    return re_encrypted_key_path

def main():

   #Decrypt CP-ABE -> Cost Old Policy 
   #Encrypt CP-ABE -> Cost New Policy  

   rv1name = "test1"
   numberOfNewPolicy = 20;
   numberOfPolicy = 20;
   


   dataSizeInKb = 1000;

   policy = createPolicy(numberOfPolicy)
   newPolicy = createPolicy(numberOfNewPolicy)

   #Key Creation
   #policyForKey = createPolicyKey(numberOfPolicy)
   #print(policyForKey)

   cpabe_keyName = "TEST"

   data = createData(dataSizeInKb) #Create Data
   byte_data = data.encode('utf-8') #Convert to bytes
   rv = os.urandom(32) #Create RV

   n = len(rv) # Split RV into 2
   rv1 = rv[0:n//2] 
   rv2 = rv[n//2:]

   with open('/home/phukaokk/SIIT Project/HDIMS/Light_Med/Symkeys/{}_key.txt'.format(rv1name),'wb') as file:
      file.write(rv1)

   symkey = base64.urlsafe_b64encode(rv) #Create SymKey From RV
   
   start_sym_time = timeit.default_timer()
   ct_m = Fernet(symkey).encrypt(byte_data) #Symmetric Encryption
   stop_sym_time = timeit.default_timer()

   sym_time = stop_sym_time - start_sym_time #Timer

   start_sym_dec_time = timeit.default_timer()
   m = Fernet(symkey).decrypt(ct_m) #Symmetric Decryption
   stop_sym_dec_time = timeit.default_timer()

   sym_dec_time = stop_sym_dec_time - start_sym_dec_time #Timer
   
   start_cpabe_time = timeit.default_timer()
   encrypt_key(rv1name, policy) #CPABE Encryption
   stop_cpabe_time = timeit.default_timer()

   cpabe_time = stop_cpabe_time - start_cpabe_time #Timer

   start_cpabe_time = timeit.default_timer()
   start_cpabe_dec_time = timeit.default_timer()
   decrypt_key(rv1name, cpabe_keyName) #CPABE Decryption
   stop_cpabe_dec_time = timeit.default_timer()

   re_encrypt_key(rv1name, newPolicy) #CPABE Reencryption
   stop_cpabe_time = timeit.default_timer()

   cpabe_time = stop_cpabe_time - start_cpabe_time #Timer
   print("ReEnc Time: " + str(cpabe_time))
   


      
def createData(size):
   n = 1024 * size   # 1024 = 1 Kb of text
   return ''.join([random.choice(string.ascii_lowercase) for i in range(n)])

def createPolicy(amount):
   policies = ""
   for x in range(1, amount):
      policies = policies + "TEST" + str(x) +  " and "
   return policies + "TEST"+str(amount)

def createPolicyKey(amount):
   policies = ""
   for x in range(1, amount):
      policies = policies + "TEST" + str(x) +  " "
   return policies + "TEST"+str(amount)
   
main()