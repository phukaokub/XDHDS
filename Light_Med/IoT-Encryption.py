from operator import xor
from cryptography.fernet import Fernet
import random
import string
import hashlib, SigningPhasePerf, os, subprocess, cpabe, keygenerator, timeit, time, base64, charm
from charm.toolbox.pairinggroup import PairingGroup,ZR,G1,G2,GT,pair,extract_key
import sys
from itertools import cycle

def byte_xor(ba1, ba2):
        """ XOR two byte strings """
        return bytes([_a ^ _b for _a, _b in zip(ba1, cycle(ba2))])

def utf8len(s):
    return len(s.encode('utf-8'))

def main():

   # Enc => (data xor with random number same lenght) * number of IoT devices 

   rv1name = "test1"
   numberOfDevices = 5;
   dataSizeInKb = 2000

   xorData = []
   data = createData(dataSizeInKb) #Create Data
   byte_data = data.encode('utf-8') #Convert to bytes
   temp = ""

   #Simulate Permutation
   for i in range(numberOfDevices):
      xorData.append(createData(dataSizeInKb).encode('utf-8'))

   start_sym_time = timeit.default_timer()
   
   #Symmetric Encryption
   for i in range(numberOfDevices):

      data = bin(int.from_bytes(xorData[i], byteorder=sys.byteorder))
      xData = bin(int.from_bytes(byte_data, byteorder=sys.byteorder))

      byte_xor(xorData[i], byte_data)

   stop_sym_time = timeit.default_timer()

   sym_time = stop_sym_time - start_sym_time #Timer
   print("IoT Enc Time : " + str(sym_time)) 
      
def createData(size):
   n = 1024 * size   # 1024 = 1 Kb of text
   return ''.join([random.choice(string.ascii_lowercase) for i in range(int(n))])

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
