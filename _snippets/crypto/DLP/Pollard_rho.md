---
title: "Pollard's rho 法"
permalink: /snippets/pollards-rho
writer: anko9801
layout: library
---

## 説明

$\rho$ 法は文字 $\rho$ の形が由来となっていて、まず、ある点を決めます。そして疑似ランダム関数 $f$ にその点を入れると次の点が出ます。今まで出た点と衝突したらDLPが解けるという仕組みです。

$$
\begin{aligned}
x_0 &= g^{a_0} \\
x_{i+1} &= f(x_i) \\
\end{aligned}
$$

$x_i = x_j$
具体的には $t = ax + b$
誕生日のパラドックス

$$
f(x)=
\begin{cases}
yx & (x \in G_1 \rm{のとき}) \\
x^2 & (x \in G_2 \rm{のとき})\\
gx & (x \in G_3 \rm{のとき})\\
\end{cases}
$$

$$
f(X)=
\begin{cases}
Y+X & (X \in P_1 \rm{のとき}) \\
2X & (X \in P_2 \rm{のとき})\\
G+X & (X \in P_3 \rm{のとき})\\
\end{cases}
$$

$$
\begin{aligned}
x_0 &= g^{a_0}y^{b_0} \\
x_i &= g^{a_i}y^{b_i} \\

a_{i+1} &=
\begin{cases}
a_i & (x \in G_1 \rm{のとき}) \\
2a_i & (x \in G_2 \rm{のとき})\\
a_i + 1 & (x \in G_3 \rm{のとき})\\
\end{cases}
& b_{i+1} &=
\begin{cases}
b_i + 1 & (x \in G_1 \rm{のとき}) \\
2b_i & (x \in G_2 \rm{のとき})\\
b_i & (x \in G_3 \rm{のとき})\\
\end{cases}\\

x_i &= x_j \\
g^{a_i}y^{b_i} &= g^{a_j}y^{b_j} \\
g^{a_i - a_j} &= g^{x(b_j - b_i)} \\
x &= (a_i - a_j)(b_j - b_i)^{-1} \pmod{p-1} \\
\end{aligned}
$$

Pollard's Kangaroo 法 (Lambda 法)
$\rho$ 法は動く点が1つの値だったのに対し、 $\lambda$ 法は2つの値がランダムに動いていき、一方がもう一方の点に衝突したときDLPが解ける。

$$
\begin{aligned}
x_0 &= g^{a_0} & y_0 &= g^{b_0} \\
x_{i+1} &= x_ig^{r(x_i)} & y_{i+1} &= y_i g^{r(y_i)} \\
\end{aligned}
$$

$x_i = y_j$ となるとき

## 実装

## 使用例

## 参考
