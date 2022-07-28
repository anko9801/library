---
title: "Boneh-Durfee Attack"
permalink: /snippets/boneh-durfee
writer: anko9801
layout: library
---

## 説明

$e$ が大きすぎると以下の式に対し Coppersmith Method を用いて攻撃できる。

$$
\begin{aligned}
ed &= 1 & \pmod{\phi} \\
ed &= k \phi + 1 & (\mathrm{over}\ \mathbb{Z}) \\
0 &= k \phi + 1 & \pmod e \\
&= k (N + 1 - p - q) + 1 & \pmod e \\
&= 2k \left(\frac{N + 1}{2} + \frac{-p -q}{2}\right) + 1 & \pmod e \\
\end{aligned}
$$

## 実装

{% include python.html code="crypto/RSA/boneh_durfee.sage" %}

## 使用例
