import sys
from CP_ABE import CPabe_BSW07
from charm.toolbox.pairinggroup import PairingGroup, GT

def setup():
    group = PairingGroup('SS512')
    cpabe = CPabe_BSW07(group)
    public_key, master_key = cpabe.setup()
    print("Public key:", public_key)
    print("Master key:", master_key)

def keygen(attributes):
    group = PairingGroup('SS512')
    cpabe = CPabe_BSW07(group)
    # Parse attributes from command-line arguments
    attributes = attributes.split(',')
    public_key, master_key = cpabe.setup()
    secret_key = cpabe.keygen(public_key, master_key, attributes)
    print("Secret key:", secret_key)

def encrypt(message, access_policy):
    group = PairingGroup('SS512')
    cpabe = CPabe_BSW07(group)
    public_key, _ = cpabe.setup()
    cipher_text = cpabe.encrypt(public_key, message, access_policy)
    print("Ciphertext:", cipher_text)

def decrypt(cipher_text, attributes):
    group = PairingGroup('SS512')
    cpabe = CPabe_BSW07(group)
    public_key, master_key = cpabe.setup()
    secret_key = cpabe.keygen(public_key, master_key, attributes.split(','))
    decrypted_message = cpabe.decrypt(public_key, secret_key, cipher_text)
    print("Decrypted message:", decrypted_message)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python cpabe_cli.py <command> [<args>]")
        sys.exit(1)
    
    command = sys.argv[1]
    if command == "setup":
        setup()
    elif command == "keygen":
        keygen(sys.argv[2])
    elif command == "encrypt":
        encrypt(sys.argv[2], sys.argv[3])
    elif command == "decrypt":
        decrypt(sys.argv[2], sys.argv[3])
    else:
        print("Unknown command:", command)
        sys.exit(1)
