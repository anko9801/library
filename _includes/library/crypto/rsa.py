from Crypto.Util.number import *

p = getPrime(512)
q = getPrime(512)
N = p * q
phi = (p - 1) * (q - 1)
e = 65537
d = pow(e, -1, phi)


def encrypt(plaintext):
    m = bytes_to_long(plaintext)
    c = pow(m, e, N)
    cipher = long_to_bytes(c)
    return cipher


def decrypt(cipher):
    c = bytes_to_long(cipher)
    m = pow(c, d, phi)
    plaintext = long_to_bytes(m)
    return plaintext


cipher = encrypt(b"This is RSA")
print(cipher)
plaintext = decrypt(cipher)
print(plaintext)
