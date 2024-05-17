import subprocess
#enc the symkey with policy dataowner or medicalstaff
#id = "p0000"
def encrypt_key(id, policy):
    p = subprocess.run(['cpabe-enc', '-k','/home/user/Light_Med/LightMed/pub_key', '/home/user/Light_Med/LightMed/Symkeys/{}_key.txt'.format(id), '{}'.format(policy)])
def encrypt_text(dir, policy):
    p = subprocess.run(['cpabe-enc','/home/user/Light_Med/LightMed/pub_key', '/home/user/Light_Med/LightMed/{}'.format(dir), policy])
#dec the symkey with dataowner's private key
# def decrypt_key(id):
#     p = subprocess.call(["cpabe-dec", "pub_key", "DO00000_priv_key", "./Symkeys/{}_key.txt.cpabe".format(id)])
def decrypt(file, key):
    p = subprocess.run(['cpabe-dec', '-k','/home/user/Light_Med/LightMed/pub_key', '/home/user/Light_Med/LightMed/cpabe_keys/{}_priv_key'.format(key), '/home/user/Light_Med/LightMed/Symkeys/{}_key.txt.cpabe'.format(file)])
    #p = subprocess.call(["cpabe-dec", "-k","pub_key", "./cpabe_keys/DO00000_priv_key", "{}".format(file)])
def keygen(id,policy):
    p = subprocess.run(['cpabe-keygen','-o','/home/user/Light_Med/LightMed/cpabe_keys/{}_priv_key'.format(id),'/home/user/Light_Med/LightMed/pub_key','/home/user/Light_Med/LightMed/master_key', '{}'.format(policy)])
#p = subprocess.call(["mv", "{}_key.txt.cpabe".format(id), "{}_key.txt".format(id)])
#decrypt("./patientCloud/p01000.txt.cpabe")
#encrypt_text("p00010")
# policyarray = ["dataowner","medicalstaff","a","b","c","d","e","f","g","h"]
# inputpolicy = ""
# for i in range(10):
#     policy = policyarray[i]+" "
#     inputpolicy += policy
#     keygen("DO000{}".format(i),"inputpolicy")
#     #print(inputpolicy)
#keygen("DO00000","dataowner")
#decrypt("./SymkeyCloud/p0000_key.txt.cpabe")
