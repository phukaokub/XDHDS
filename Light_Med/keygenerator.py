from cryptography.fernet import Fernet
from Crypto.PublicKey import RSA
def rsakeygenerator(): #For generating the key for a new section
    rsa_key = RSA.generate(1024)
    f = open('DO0000_RSA_privkey.pem','wb')
    f.write(rsa_key.export_key('PEM'))
    f.close()
    f = open('DO0000_RSA_pubkey.pem','wb')
    f.write(rsa_key.public_key().export_key('PEM'))
    f.close()
    
def symkeygenerator(name): #For regenerating the existed section key
    key = Fernet.generate_key()
    with open('/home/user/Light_Med/Light_Med/Symkeys/{}_key.txt'.format(name),'wb') as file:
        file.write(key)
    return key
# def re_adminkeygenerator(): #For regenerating the admin section key
#     key = Fernet.generate_key()
#     with open('admin.key','wb') as file:
#         file.write(key)
#rsakeygenerator()
