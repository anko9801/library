---
title: "RSA暗号"
permalink: /snippets/rsa
writer: anko9801
layout: library
---

## 説明

暗号化
$c = m^{e} \pmod N$ を計算します。

1. 秘密鍵である大きな素数 $p, q$ を生成し、公開鍵 $N = pq$ を公開します。
2. そして数値化した平文 $m$ に対して暗号文 $c$ は $c = m^e \pmod N$ となります。

復号化
$m = c^{e^{-1}} \pmod N$ を計算します。

1. まず秘密鍵 $\phi(N) = (p - 1)(q - 1)$ を計算する。
2. $c$ に対して $d = e^{-1} \pmod{\phi(N)}$ 乗することで復号できます。

$$
\begin{aligned}
c &≡ m^e &\pmod N \\
c^d &≡ m^{ed} ≡ m &\pmod N
\end{aligned}
$$

これはオイラーの定理より肩の数が $\phi(N)$ を法として計算できるからです。

$$
\begin{aligned}
m^{\phi(N)} &≡ m^{(p - 1)(q - 1)} ≡ 1 & \pmod N \\
m^{ed} &= m^{k\phi(N) + 1} ≡ m^{k\phi(N)}m ≡ m & \pmod N \\
ed &= k\phi(N) + 1 ≡ 1 & \pmod{\phi(N)}
\end{aligned}
$$

ここで $N, e$ を知っていても $p, q, d$ を知らないとき、暗号化は簡単でも復号化は難しいという事が知られています。これを用いた暗号をRSA暗号 (Rivest-Shamir-Adleman encryption) と呼びます。

具体的には次の手順で暗号化された通信します。

1. AliceがBobに公開鍵 $N, e$ を渡す
2. Bobは公開鍵を用いて平文を暗号化
3. BobからAliceへ暗号文を送る
4. Aliceは秘密鍵 $p, q$ を用いて復号化し、平文を得る

ここに図

このようにして送っている最中に盗聴されても秘密鍵がなければ解読できず、安全な通信ができます。
またこれは一方向通信ですが、逆も同様に行えば双方向通信もできます。

### RSA-CRT

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

## 実装

{% include python.html code="crypto/RSA/rsa.py" %}

## 使用例
