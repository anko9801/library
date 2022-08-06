---
title: "Pohlig-Hellman Attack"
permalink: /snippets/pohlig-hellman-ec
writer: anko9801
layout: library
---

## 説明

中国剰余定理を用いて大きな群を複数の小さな群の直積に分ける。

楕円曲線暗号の楕円曲線の位数は細かく素因数分解できることが多い。

楕円曲線の位数 $\\#E = p_1^{e_1}p_2^{e_2}\ldots p_k^{e_k}$ と素因数分解できる。$Q = dP$ となるとき次のように $d_i$ を置く。

$$
\begin{aligned}
d_1 &= d \pmod{p_1^{e_1}} \\
d_2 &= d \pmod{p_2^{e_2}} \\
&\vdots \\
d_k &= d \pmod{p_k^{e_k}} \\
\end{aligned}
$$

それぞれの $d_i$ について次のように書ける。

$$
d_i=z_0+z_1p_i+z_2p_i^2+\ldots+z_{e_i−1}p_i^{e_i−1} \pmod{p_i^{e_i}} \quad (∀k:z_k \in [0,p_i))
$$

ここで $P_i=\frac{\\#E}{p_i}P, Q_i=\frac{\\#E}{p_i}Q$ とおくと

$$
Q_i = d_iP_i = (z_0+z_1p_i+z_2p_i^2+\ldots+z_{e_i−1}p_i^{e_i−1})P_i = z_0P_i
$$

となり, $z_0 < p_i$ である $Q_i = z_0P_i$ についてDLPを解けば良い。

他については $Q_i' = (Q_i - z_0P_i) / p_i$ とおいて同様に解けると思っていたけどECCのDDH問題から不可能かも。

## 実装

{% include python.html code="crypto/ECC/pohlig_hellman.sage" %}

## 使用例

## 参考
