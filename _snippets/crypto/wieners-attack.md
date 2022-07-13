---
title: "Wiener's Attack"
permalink: /snippets/wieners-attack
writer: anko9801
layout: library
---

## 説明

$$e$$ が大きすぎると (または $$d$$ が小さすぎると)、$$e/N$$ に対しディオファントス近似することで $$k/d$$ が求まる。
厳密には $$3d < N^{\frac{1}{4}}$$ であることが条件である。

$$
\begin{aligned}
ed &≡ 1 = k\phi(N) + 1 = k(N - p - q + 1) + 1 \\
\frac{e}{N} &= \frac{k}{d}\left(1-\frac{p + q - 1 - \frac{1}{k}}{N}\right) \approx \frac{k}{d} \\
\frac{e}{N} &\approx q_0 + \cfrac{1}{q_1 + \cfrac{1}{q_2 + \cfrac{1}{\ddots \cfrac{}{q_{m-1} + \cfrac{1}{q_m}}}}} = \frac{k_m}{d_m} \\
\end{aligned}
$$

$$
\begin{aligned}
r_{-2} &= e & k_{-2} &= 0 &d_{-2} &= 1 \\
r_{-1} &= N & k_{-1} &= 1 &d_{-1} &= 0 \\
r_{i-2} \div r_{i-1} &= q_{i} \cdots r_{i} & k_i &= q_i k_{i−1} + k_{i−2} &d_i &= q_i d_{i−1}+d_{i−2} \\
\end{aligned}
$$

## 実装

{% include python.html code="crypto/wieners_attack.py" %}

## 使用例
