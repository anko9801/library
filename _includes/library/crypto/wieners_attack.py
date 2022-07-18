import gmpy2


def convergents(a, b):
    r0, r1 = a, b
    a0, a1 = 0, 1
    b0, b1 = 1, 0

    i = 0
    while r1 != 0:
        i += 1
        q = r0 // r1
        r0, r1 = r1, r0 % r1
        a0, a1 = a1, q*a1 + a0
        b0, b1 = b1, q*b1 + b0

        if i % 2 == 0:
            a = a1 + a0
            b = b1 + b0
        else:
            a = a1
            b = b1

        yield a, b


def has_integer_roots(a, b, c):
    D = b*b - 4*a*c
    if D > 0:
        sD = gmpy2.isqrt(D)
        if sD * sD == D and (-b + sD) % (2*a) == 0:
            return 2
    elif D == 0 and b % (2*a) == 0:
        return 1
    return 0


def WienersAttack(n, e):
    for d, k in convergents(n, e):
        if k == 0 or (e * d - 1) % k != 0:
            continue
        phi = (e * d - 1) // k
        s = n - phi + 1
        if has_integer_roots(1, -s, n) > 0:
            return d
    return -1
