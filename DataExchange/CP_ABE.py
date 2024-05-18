'''
John Bethencourt, Brent Waters (Pairing-based)
 
| From: "Ciphertext-Policy Attribute-Based Encryption".
| Published in: 2007
| Available from: 
| Notes: 
| Security Assumption: 
|
| type:           ciphertext-policy attribute-based encryption (public key)
| setting:        Pairing

:Authors:    J Ayo Akinyele
:Date:            04/2011

:Modified by: Teerawat Chupahanngam
:Date: 05/2024
'''
from charm.toolbox.pairinggroup import PairingGroup, ZR, G1, G2, GT, pair
from charm.toolbox.secretutil import SecretUtil
from charm.toolbox.ABEnc import ABEnc, Input, Output

# type annotations
pk_t = {'g': G1, 'g1': G1, 'e': pair, 'G1': G1, 'GT': GT, 'alpha': ZR, 'beta': ZR, 'H1': object, 'H2': object}
mk_t = {'alpha': ZR, 'g_alpha': G1}
sk_t = {'D': G2, 'Dj': G2, 'Djp': G1, 'S': str}
ct_t = {'C_tilde': GT, 'C': G1, 'Cy': G1, 'Cyp': G2}

debug = False
class CPabe_BSW07(ABEnc):
    """
    >>> from charm.toolbox.pairinggroup import PairingGroup, ZR, G1, G2, GT, pair
    >>> group = PairingGroup('SS512')
    >>> cpabe = CPabe_BSW07(group)
    >>> msg = group.random(GT)
    >>> attributes = ['ONE', 'TWO', 'THREE']
    >>> access_policy = '((four or three) and (three or one))'
    >>> (master_public_key, master_key) = cpabe.setup()
    >>> secret_key = cpabe.keygen(master_public_key, master_key, attributes)
    >>> cipher_text = cpabe.encrypt(master_public_key, msg, access_policy)
    >>> decrypted_msg = cpabe.decrypt(master_public_key, secret_key, cipher_text)
    >>> msg == decrypted_msg
    True
    """ 
         
    def __init__(self, groupObj):
        ABEnc.__init__(self)
        global util, group
        util = SecretUtil(groupObj, verbose=False)
        group = groupObj

    @Output(pk_t, mk_t)
    def setup(self):
        g = group.random(G1)
        g1 = group.random(G1)
        p = group.order()
        e = pair
        G1_group = G1
        GT_group = GT
        
        alpha = group.random(ZR)
        beta = group.random(ZR)
        
        MSK = g ** alpha
        PK = (e(g, g) ** alpha, g ** beta)
        
        H1 = lambda x: group.hash(x, ZR)
        H2 = lambda x: group.hash(x, G1)
        
        PP = {
            'g': g,
            'g1': g1,
            'p': p,
            'e': e,
            'G1': G1_group,
            'GT': GT_group,
            'alpha': alpha,
            'beta': beta,
            'H1': H1,
            'H2': H2
        }
        
        mk = {'alpha': alpha, 'g_alpha': MSK}
        pk = PP
        return (pk, mk)

    @Input(pk_t, mk_t, [str])
    @Output(sk_t)
    def keygen(self, pk, mk, S):
        r = group.random()
        g_r = (pk['g1'] ** r)
        D = (pk['g1'] ** mk['alpha']) * g_r
        
        D_j, D_j_pr = {}, {}
        for j in S:
            r_j = group.random()
            D_j[j] = g_r * (group.hash(j, G2) ** r_j)
            D_j_pr[j] = pk['g'] ** r_j
        return {'D': D, 'Dj': D_j, 'Djp': D_j_pr, 'S': S}

    @Input(pk_t, GT, str)
    @Output(ct_t)
    def encrypt(self, pk, M, policy_str):
        policy = util.createPolicy(policy_str)
        a_list = util.getAttributeList(policy)
        s = group.random(ZR)
        shares = util.calculateSharesDict(s, policy)
        
        C = pk['g'] ** s
        C_y, C_y_pr = {}, {}
        for i in shares.keys():
            j = util.strip_index(i)
            C_y[i] = pk['g'] ** shares[i]
            C_y_pr[i] = group.hash(j, G2) ** shares[i]
        
        return {
            'C_tilde': (pk['e'](pk['g'], pk['g']) ** s) * M,
            'C': C, 'Cy': C_y, 'Cyp': C_y_pr,
            'policy': policy_str, 'attributes': a_list
        }

    @Input(pk_t, sk_t, ct_t)
    @Output(GT)
    def decrypt(self, pk, sk, ct):
        policy = util.createPolicy(ct['policy'])
        pruned_list = util.prune(policy, sk['S'])
        if pruned_list == False:
            return False
        z = util.getCoefficients(policy)
        A = 1
        for i in pruned_list:
            j = i.getAttributeAndIndex()
            k = i.getAttribute()
            A *= (pair(ct['Cy'][j], sk['Dj'][k]) / pair(sk['Djp'][k], ct['Cyp'][j])) ** z[j]
        
        return ct['C_tilde'] / (pair(ct['C'], sk['D']) / A)