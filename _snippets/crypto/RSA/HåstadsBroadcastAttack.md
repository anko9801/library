---
title: "Håstad’s Broadcast Attack"
permalink: /snippets/hastads-broadcast
writer: anko9801
layout: library
---

## 説明

平文を互いに素な $N_1, \ldots, N_e$ で暗号化された暗号文が分かっているとき、中国剰余定理を用いて $m$ を求められる。

$$
\begin{aligned}
c_1 &≡ m^e \pmod{N_1} \\
c_2 &≡ m^e \pmod{N_2} \\
\vdots \\
c_e &≡ m^e \pmod{N_e} \\
m^e &≡ CRT(c_1, c_2, \dots , c_e) \pmod{N_1N_2\cdots N_e} \\
m^e &= CRT(c_1, c_2, \dots , c_e)
\end{aligned}
$$

## 実装


## 使用例

## 関連

- [They Were Eleven - BSides Ahmedabad CTF 2021 author's writeup](https://furutsuki.hatenablog.com/entry/2021/12/07/020611)
