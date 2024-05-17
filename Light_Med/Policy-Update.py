from operator import xor
from cryptography.fernet import Fernet
import random
import string
import hashlib, SigningPhasePerf, os, subprocess, cpabe, keygenerator, timeit, time, base64, charm
from charm.toolbox.pairinggroup import PairingGroup,ZR,G1,G2,GT,pair,extract_key

def utf8len(s):
    return len(s.encode('utf-8'))

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

   with open('/home/user/Light_Med/LightMed/Symkeys/{}_key.txt'.format(rv1name),'wb') as file:
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
   cpabe.encrypt_key(rv1name, policy) #CPABE Encryption
   stop_cpabe_time = timeit.default_timer()

   cpabe_time = stop_cpabe_time - start_cpabe_time #Timer

   start_cpabe_time = timeit.default_timer()
   start_cpabe_dec_time = timeit.default_timer()
   cpabe.decrypt(rv1name, cpabe_keyName) #CPABE Decryption
   stop_cpabe_dec_time = timeit.default_timer()

   cpabe.encrypt_key(rv1name, newPolicy) #CPABE Reencryption
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
