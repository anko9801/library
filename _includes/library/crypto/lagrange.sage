def lagrange(b1, b2):
    if b1.norm() > b2.norm():
        b1, b2 = b2, b1
    while b1.norm() < b2.norm():
        q = - round(b1.dot_product(b2) / b1.norm() ^ 2)
        b1, b2 = b2 + q * b1, b1
    return b2, b1
