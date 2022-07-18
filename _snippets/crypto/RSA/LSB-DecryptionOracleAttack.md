---
title: "LSB Decryption Oracle Attack"
permalink: /snippets/lsb-decryption-oracle
writer: anko9801
layout: library
---

## 説明

全てが分かっていなくとも偶奇さえ分かれば任意の暗号文を復号できる。
ある暗号文 $c$ に対し、$2^e$ をx回掛けた値を復号した下位1bitを得て平文を求めます。得られる下位1bitは次の関数 $f(x)$ を用いて $f(x) \bmod 2$ と表せられます。decは復号化関数です。

$$
\begin{aligned}
f(x) &= Dec(2^{ex}c \bmod N) = 2^xm \bmod N \\
\end{aligned}
$$

$x = 1$ のとき
まず $0 \leq m < N$ であるから $f(1)$ は $2m \bmod N = 2m, 2m - N$ のどちらかとなる。また $2m$ は偶数、$N$ は奇数であるから $f(1)$ が偶数か奇数かで $2m, 2m - N$ のどちらかが分かります。すると $m$ が存在する区間が分かります。

$$
\begin{aligned}
&f(1) = 2m \bmod N \\
&
\begin{cases}
    f(1) \bmod 2 = 1 \Leftrightarrow f(1) = 2m - N & \Leftrightarrow \frac{N}{2} \leq m < N \\
    f(1) \bmod 2 = 0 \Leftrightarrow f(1) = 2m & \Leftrightarrow 0 \leq m < \frac{N}{2} \\
\end{cases}
\end{aligned}
$$

つまり $m$ は $[0, N)$ の範囲に対して最下位ビットが1のとき区間の右半分、0のとき区間の左半分だと言えます。

$x = 2$ のとき
前の結果を用いて場合分けして考えると同様の考え方で次のように導けます。

$$
\begin{aligned}
f(2) &= 2(2m \bmod N) \bmod N \\
f(1) &= 2m - N \Rightarrow f(2) = 4m - 2N \bmod N \\
&
\begin{cases}
    f(2) \bmod 2 = 1 \Leftrightarrow f(2) = 4m - 3N & \Leftrightarrow \frac{3N}{4} \leq m < N \\
    f(2) \bmod 2 = 0 \Leftrightarrow f(2) = 4m - 2N & \Leftrightarrow \frac{N}{2} \leq m < \frac{3N}{4} \\
\end{cases}
\\
f(1) &= 2m \Rightarrow f(2) = 4m \bmod N \\
&
\begin{cases}
    f(2) \bmod 2 = 1 \Leftrightarrow f(2) = 4m - N & \Leftrightarrow \frac{N}{4} \leq m < \frac{N}{2} \\
    f(2) \bmod 2 = 0 \Leftrightarrow f(2) = 4m & \Leftrightarrow 0 \leq m < \frac{N}{4} \\
\end{cases}
\end{aligned}
$$

つまり $m$ は $[0, N/2)$ 、 $[N/2, N)$ のそれぞれの範囲に対して最下位ビットが1のとき区間の右半分、0のとき区間の左半分だと言えます。

$x \geq 3$ のときも同様に行って $m$ の値を求めることができます。

## 実装


## 使用例


## 参考

