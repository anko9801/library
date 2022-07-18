---
title: "Franklin-Reiter Related Message Attack"
permalink: /snippets/franklin-reiter
writer: anko9801
layout: library
---

## 説明

$f(m_1) = m_2$
$m_1 = pad_1 + m, m_2 = pad_2 + m, m_2 = m_1 + (pad_2 - pad_1)$

$$
\begin{aligned}
c_1 &= m_1^{e_1} & \pmod N \\
c_2 &= m_2^{e_2} = f(m_1)^{e_2} & \pmod N \\
x - m_1 &= \gcd(x^{e_1} - c_1, f(x)^{e_2} - c_2) & \pmod N \\
\end{aligned}
$$

## 実装


## 使用例


## 参考

