def size_reduction(B):
    n = len(B)
    B = matrix(B)
    G, mu = B.gram_schmidt()
    for i in range(n):
        for j in range(i - 1, -1, -1):
            if mu[i][j].abs() > 1 / 2:
                q = mu[i][j].round()
                B[i] -= q * B[j]
                mu[i] -= q * mu[j]
    return B


B = [vector([5, -3, -7]), vector([2, -7, -7]), vector([3, -10, 0])]
print(size_reduction(B))
