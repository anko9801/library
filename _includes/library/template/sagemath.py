# 整数環
ZZ
#
PolynomialRing(ZZ)
PolynomialRing(Zmod(N))
small_roots()

M = matrix(QQ, [[1, 2], [3, 4]])
M.LLL()

set(factor(n))

Zn = Zmod(N)
P. < x > = PolynomialRing(Zn)
R = GF(2 ^ m)
R.fetch_int(12)

p /= p.leading_coefficient()  # 最高次項 モニック化
p = p.monic()
ideal(f).groebner_basis()

A = matrix(Zn, [
    [_a, _b, _c, _d, _e],
    [1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0],
    [0, 0, 1, 0, 0],
    [0, 0, 0, 1, 0],
])

b11, b12, b13, b14, b15 = map(int, (A ^ e)[4])

D, P = m.eigenmatrix_left()
P ^ (-1)*D*P == m

Q = diagonal_matrix(weights)

B *= Q
B = B.LLL()
B /= Q

EllipticCurve()
