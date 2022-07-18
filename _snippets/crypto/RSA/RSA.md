---
title: "RSA暗号"
permalink: /snippets/rsa
writer: anko9801
layout: library
---

## 説明

事前に大きな素数 $p, q$ を生成し、 $N = pq$ を公開します。そして数値化した平文 $m$ に対して $e$ 乗して $N$ で割った余りである $m^e \bmod N$ を暗号文 $c$ とします。これが暗号化の処理となります。そして復号化についてはまず $\phi(N) = (p - 1)(q - 1)$ を計算して、 $c$ を $e$ の $\mod \phi(N)$ 上の逆元 $d = e^{-1}$ 乗することで $m$ を復号できます。

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

## 実装

{% include python.html code="crypto/rsa.py" %}

## 使用例
