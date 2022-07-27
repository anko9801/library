def LLL(B, delta):
    n = len(B)
    assert 1 / 4 < delta < 1
    B = matrix(B)
    i = 1
    G, mu = B.gram_schmidt()
    while i < n:
        for j in range(i - 1, -1, -1):
            print(i, j)
            if mu[i][j].abs() > 1 / 2:
                q = mu[i][j].round()
                B[i] -= q * B[j]
                mu[i] -= q * mu[j]
        if B[i].norm() >= (delta - mu[i][i - 1] ^ 2) * B[i - 1].norm():
            i += 1
        else:
            B[i - 1], B[i] = B[i], B[i - 1]
            mu = GSOUpdate(B, mu, i)
            i = max(i - 1, 1)
    return B


def GSOUpdate(B, mu, i):
    n = B.nrows()
    nu = mu[i][i - 1]
    b = B[i] + nu ^ 2 * B[i - 1]
    print(nu, B[i - 1], b)
    mu[i][i - 1] = nu * B[i - 1] / b
    B[i] = B[i] * B[i - 1] / b
    B[i - 1] = b
    for j in range(i - 1):
        mu[i - 1][j], mu[i][j] = mu[i][j], mu[i - 1][j]
    for k in range(i + 1, n):
        t = mu[k][i]
        mu[k][i] = mu[k][i - 1] - nu * t
        mu[k][i - 1] = t + mu[i][i - 1] * mu[k][i]
    return mu


B = [vector([5, -3, -7]), vector([2, -7, -7]), vector([3, -10, 0])]
print(LLL(B, 0.8))
