---
title: "Partial Key Exposure Attack"
permalink: /snippets/partial-key
writer: anko9801
layout: library
---

## 説明

秘密鍵を部分的に知っていさえいれば、Coppersmith Method を用いて解けてしまう。
$n$ を $N$ のビット数とする。

### $p, q$ のどちらかを $n/4$ ビット程度知っているとき

$$
\begin{aligned}
f(x) &= p_{upper} + x & \pmod p \\
f(x) &= 2^{k}x + p_{lower} & \pmod p \\
f(x,y) &= 2^kx + p_{mid} + y & \pmod p \\
\end{aligned}
$$

### 平文 $m$ のビットを $(1-1/e)n$ 程度知っているとき

$$
\begin{aligned}
f(x) &= (m_{upper} + x)^e - c & \pmod N \\
f(x) &= (2^kx + m_{lower})^e - c & \pmod N \\
f(x,y) &= (2^kx + m_{mid} + y)^e - c & \pmod N \\
\end{aligned}
$$

### $d$ を $n/4$ ビット程度知っているとき

$e$ が総当り出来るくらい小さいときに $d$ を $n/4$ ビットだけ知っていれば元の $d$ を構成できる。大体の場合は $e = 65537$ であるから十分可能である。$d < \phi(N)$ より $0 < k \leq e$ となり、この $k$ に対して総当たりする。

- 上位ビットの場合
$d$ と $p, q$ の関係式を立てる。

$$
\begin{aligned}
ed &= 1 & \pmod{\phi(N)} \\
ed &= 1 + k(N - p - q + 1) \\
d &= \frac{kN}{e} - \frac{k(p+q-1) -1}{e} \\
e(d_{upper} + x) &= - k (y - 1) + 1 & \pmod N \\
\end{aligned}
$$

第三式について $p + q \approx \sqrt{N}$ より第二項は上位ビットに関連する情報を持たない。これより第一項の $k$ について総当りして上位ビットと一致する $k$ を見つければよい。すると第4式に対し Multivariate CopperSmith を用いて、$d$ がわかる。

- 下位ビットの場合
$d$ の下位ビットから $k$ について総当りして $p$ の下位ビットを求める。すると先程の問題に帰着できて $p$ がわかり $d$ がわかる。

$$
\begin{aligned}
ed &= 1 + k\left(N - p - \frac{N}{p} + 1\right) \\
edp &= p + kp(N - p + 1) - kN & \pmod {2^{n/4}} \\
\end{aligned}
$$

### CRTの秘密鍵 $d$ のビットを $n/4$ 程度知っているとき

上と同様にして解けます。

$$
\begin{aligned}
ed_p &= 1 & \pmod{p-1} \\
ed_p &= 1 + k_p(p − 1) \\
\end{aligned}
$$

## 実装

{% include python.html code="crypto/RSA/partial_key_exposure.sage" %}

## 使用例

{% include python.html code="crypto/RSA/partial_key_exposure_ex.sage" %}

## 参考

