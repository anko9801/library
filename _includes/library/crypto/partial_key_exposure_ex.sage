from Crypto.Util.number import *

p = getPrime(512)
q = getPrime(512)
n = p * q
e = 3

beta = 0.5
epsilon = beta^2/7

pbits = p.nbits()
kbits = floor(n.nbits() * (beta^2 - epsilon))
# p upper
pbar = p & (2^pbits - 2^kbits)

print(f"upper {pbits - kbits} bits (of {pbits} bits) is given")

PR.<x> = PolynomialRing(Zmod(n))
f = x + pbar

print(p)
x0 = f.small_roots(X=2^kbits, beta=0.3)[0]
print(x0 + pbar)
