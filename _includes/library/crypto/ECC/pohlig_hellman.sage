fact = factor(G.order())
ord = int(G.order())
dlogs = []
for p, e in fact:
    t = ord // p ^ e
    dlog = discrete_log(t * Q, t * G, operation="+")
    dlogs += [dlog]

print(crt(dlogs, primes))
