---
title: "Pohlig-Hellman Attack"
permalink: /snippets/pohlig-hellman-ec
writer: anko9801
layout: library
---

## 説明

$$
\begin{aligned}
\#E &= 楕円曲線上の点の数 \\
\#P &= n : P = nP \\
\#E &= q_1q_2 \\
\#P &\mid \#E \\
\#P &= 1, q_1, q_2, q_1q_2
\end{aligned}
$$

中国剰余定理を用いて大きな問題を小さな問題に分割する。

オイラーの定理で剰余とって中国剰余定理

because factoring the generator's order produces many (actually not, but it is enough) small primes:

```
[In] factor(G.order())
[Out] 2 * 5 * 11 * 22303 * 36209 * 196539307
```

$$
\begin{aligned}
d &= d_1 \pmod{p_1^{e_1}} \\
d &= d_2 \pmod{p_2^{e_2}} \\
&\vdots \\
d &= d_k \pmod{p_k^{e_k}} \\
\end{aligned}
$$

それぞれの $d_i$ について次のように書ける。
$d_i=z_0+z_1p_i+z_2p_i^2+\ldots+z_{e_i−1}p_i^{e_i−1} \pmod{p_i^{e_i}} \quad (∀k:z_k \in [0,p_i−1])$
ここで $P_i=\frac{\#E}{p_i}P, Q_i=\frac{\#E}{p_i}Q$ とおくと、$Q_i = d_iP_i = (z_0+z_1p_i+z_2p_i^2+\ldots+z_{e_i−1}p_i^{e_i−1})P_i = z_0P_i$
となり、$z_0 < p_i \leq p_i^{e_i} \leq p$ である $Q_i = z_0P_i$ についてDLPを解く。

```
fact = factor(G.order())
ord = int(G.order())
dlogs = []
for p, e in :
  t = ord // p^e
  dlog = discrete_log(t*Q, t*G, operation="+")
  dlogs += [dlog]

print(crt(dlogs, primes))
```

## 実装

## 使用例

## 参考
