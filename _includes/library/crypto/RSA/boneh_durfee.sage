load('coppersmith.sage')

def boneh_durfee(N, e):
    bounds = (floor(N^.25), 2^1024)
    P.<k, s> = PolynomialRing(Zmod(e))
    f = 2*k*((N+1)//2 - s) + 1
    print(small_roots(f, bounds, m=3, d=4))
