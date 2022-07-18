---
title: "RSA-CRT Fault Attack"
permalink: /snippets/rsa-crt-fault
writer: anko9801
layout: library
---

## 説明

RSAの復号をする際に $c^d$ を計算しますが、 $d = e^{-1} \pmod {\phi (N)}$ は比較的大きいので処理が重くなります。これに対してRSA-CRTは中国剰余定理(CRT)を利用して高速化を図っています。

$$
\begin{aligned}
m_p &= c^{d \ \bmod \ p−1} & \pmod p \\
m_q &= c^{d \ \bmod \ q−1} & \pmod q \\
m &= \mathrm{CRT}(m_p, m_q) & \pmod {N} \\
&= m_q + (m_p - m_q) (q^{-1} \bmod p) q & \pmod {N} \\
\end{aligned}
$$

これより下の値を秘密鍵として持つことになります。

$$
\begin{aligned}
d_p &= d \bmod p−1 \\
d_q &= d \bmod q−1 \\
q_{inv} &= q^{-1} \bmod p \\
\end{aligned}
$$

しかし $d_p, d_q$ のどちらかが何らかの方法で書き換えられてしまったとき次のようにできます。

$$
\begin{aligned}
m_p &= c^{d_p} \pmod p \\
m_q' &= c^{d_q'} \pmod q \\
m &= CRT(m_p, m_q) = kp + m_p \\
m' &= CRT(m_p, m_q') = k'p + m_p \\
m - m' &= (k - k')p \\
p &= \gcd(m - m', N) \\
\end{aligned}
$$

これより平文 $m, m'$ を知ることができれば解くことができます。

## 実装


## 使用例


## 参考

