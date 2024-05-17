import base64

from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
import base64, hashlib, random, timeit, pymongo, datetime, json, math
from random import choice

def Sign(CT_byte,CT,certid,id_MD):
    
    #hash the CT
    start = timeit.default_timer()
    CT_MD = hashlib.sha256(CT_byte).hexdigest()
    CT_MD_byte = str.encode(CT_MD)
    #import pubkey
    f = open('DO0000_RSA_pubkey.pem','r')
    #f = open('{}_RSA_pubkey.pem'.format(certid),'r')
    pubkey = RSA.import_key(f.read())
    CT_RSA_Pubkey = PKCS1_OAEP.new(pubkey)
    #encrypt MD with RSA -> Get DS
    DS_byte = CT_RSA_Pubkey.encrypt(CT_MD_byte)
    #print(DS_byte)
    stop = timeit.default_timer()
    runtime1 = stop-start

    DS = DS_byte.decode('ISO-8859-1')
    #print(len(DS))
    #start = timeit.default_timer()
    #generate R value
    start = timeit.default_timer()
    R = []
    DS_R = ""
    while(len(R) != len(DS)):
        pickindex = random.randint(0,len(DS)-1)
        if pickindex not in R:
            R.append(pickindex)
            DS_R +=DS[pickindex]
    stop = timeit.default_timer()
    runtime2 = stop-start
    # print(len(R))
    # print("R: ",R)
    # print("DS_R: ",DS_R)

    #Define constant R
    constR = [27, 40, 6, 9, 68, 107, 123, 49, 22, 31, 127, 79, 85, 34, 71, 26, 0, 115, 121, 110, 74, 5, 36, 63, 73, 76, 39, 112, 111, 53, 70, 4, 65, 48, 126, 117, 52, 109, 67, 35, 95, 72, 94, 86, 50, 10, 118, 105, 90, 33, 102, 88, 113, 32, 61, 92, 122, 29, 16, 28, 119, 1, 114, 83, 98, 18, 77, 62, 45, 80, 38, 8, 42, 99, 13, 69, 96, 17, 20, 91, 25, 106, 19, 30, 47, 15, 3, 37, 56, 41, 46, 124, 87, 75, 89, 120, 100, 81, 97, 11, 60, 21, 104, 59, 93, 43, 66, 55, 78, 101, 64, 82, 12, 116, 7, 44, 23, 14, 58, 2, 51, 24, 108, 103, 57, 84, 54, 125]
    #Get R1
    
    R1 = []
    for i in range(len(R)):
        R1.append(R[constR[i]])
    # stop = timeit.default_timer()
    # runtime = stop - start
    
    #-------Audit Log part---------
    client = pymongo.MongoClient("mongodb+srv://Nontawat:iS1sKbQnyLO6CWDE@section1.oexkw.mongodb.net/section1?retryWrites=true&w=majority")
    mydb = client['EncryptedMTR']
    mycol = mydb['AuditLogPerf']
    
    #get private key from local, convert to string for storing on database
    f = open('DO0000_RSA_privkey.pem','r')
    #f = open('{}_RSA_privkey.pem'.format(certid),'r')
    privkey = RSA.import_key(f.read())
    privkey_byte = privkey.exportKey("PEM")
    privkey_string = privkey_byte.decode('ISO-8859-1')
    
    curtimedate = str(datetime.datetime.now())
    update = {'certid': '{}'.format(certid),'CT':'{}'.format(CT), 'PrivKey': '{}'.format(privkey_string), 'DS*R': '{}'.format(DS_R), 'R1': '{}'.format(R1)}
    #existedLog = mycol.find_one({'MD_id': id_MD})
    stop = timeit.default_timer()
    #print('Signing Time: ', stop - start)
    # if  type(existedLog) != type(None):  #If the audit log of file is existed then update the log
    #     existedLog[curtimedate] = update
    #     mycol.delete_one({'MD_id': id_MD})
    #     mycol.insert_one(existedLog)
    #     #existedLog[curtimedate] = update
    # else: #There is no audit log for this document
    #     log = {'MD_id': '{}'.format(id_MD), '{}'.format(curtimedate): update}
    #     mycol.insert_one(log)
    runtimetaggen = runtime1+runtime2
    return DS_R, R1, runtimetaggen
