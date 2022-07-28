---
title: "Pollard's rho 法"
permalink: /snippets/pollards-rho
writer: anko9801
layout: library
---

## 説明

初期点 $x_0$ と適当な副作用のない疑似乱数関数 $f(x)$ を決めて $x_{i+1} = f(x_i)$ となるように数列 $(x_0, x_1, \ldots)$ を生成する。このとき $0 \leq \exists i < \exists j < N$, $x_i = x_j$ となる $i,j$ を見つけられたらDLPが解けるという仕組みです。

よく用いられる関数 $f(x)$ は次のようなものがあります。ただし、$G_1, G_2, G_3$ は巡回群 $G$ の集合をランダムに振り分けられるように3つに区別したものです。

$$
f(x)=
\begin{cases}
bx & (x \in G_1 \mathrm{のとき}) \\
x^2 & (x \in G_2 \mathrm{のとき}) \\
ax & (x \in G_3 \mathrm{のとき}) \\
\end{cases}
$$

このとき $x_0 = a$ とすると $x_i$ は $x_i = a^{s_i}b^{t_i}$, $s_i, t_i \in \mathbb{N}$ と表せられる。すると $x_i = x_j$ において $n$ は巡回群の位数 $N$ を用いて次のように表せられる。

$$
\begin{aligned}
x_i &= a^{s_i}b^{t_i} = a^{s_i + nt_i} \\
x_j &= a^{s_j + nt_j} \\
a^{s_i - s_j} &= a^{n(t_j - t_i)} \\
n &= \frac{s_i - s_j}{t_j - t_i} \pmod N
\end{aligned}
$$

これよりDLPが解ける。
Pollard-$\rho$ 法の $\rho$ は文字 $\rho$ の形が由来となっている。

<!-- Pollard's Kangaroo 法 (Lambda 法)
$\rho$ 法は動く点が1つの値だったのに対し、 $\lambda$ 法は2つの値がランダムに動いていき、一方がもう一方の点に衝突したときDLPが解ける。

$$
\begin{aligned}
x_0 &= g^{a_0} & y_0 &= g^{b_0} \\
x_{i+1} &= x_ig^{r(x_i)} & y_{i+1} &= y_i g^{r(y_i)} \\
\end{aligned}
$$

$x_i = y_j$ となるとき -->

## 計算量

$O(\sqrt{N})$

計算量の期待値集合 $S$ に対してそれぞれ相違な $x_0, x_1, \ldots, x_{k-1}$ を選ぶ事象 $A$ と

$$
\begin{aligned}
P(A) &= \prod_{i = 0}^{k-1}\left(1-\frac{i}{N}\right) \approx \prod_{i = 0}^{k-1}e^{-i/N} \approx e^{-k^2/2N} \\
P(B) &= \frac{k}{N}e^{-k^2/2N} \\
E(B) &= \sum_{k=1}^N k\cdot\frac{k}{N}e^{-k^2/2N} \\
&\approx \sqrt{N}\int_0^\infty t^2e^{-t^2/2} dt \\
&= \sqrt{\frac{\pi N}{2}}
\end{aligned}
$$


## 実装

## 使用例

## 参考

- The Arithmetic of Elliptic Curves. p.383