---
title: "Common Modulus Attack"
permalink: /snippets/common-modulus
writer: anko9801
layout: library
---

## 説明

共通の平文を異なる $e$ で暗号化した暗号文が分かっているとき平文を求められる。

$$
\begin{aligned}
c_1 &≡ m^{e_1} & \pmod N \\
c_2 &≡ m^{e_2} & \pmod N \\
\gcd(e_1, e_2) &= s_1e_1 + s_2e_2 \\
c_1^{s_1} c_2^{s_2} &= m^{s_1e_1 + s_2e_2} = m^{\gcd(e_1, e_2)} & \pmod N
\end{aligned}
$$

## 実装


## 使用例
