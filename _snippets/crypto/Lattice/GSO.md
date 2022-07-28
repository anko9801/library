---
title: "Gram-Schmidt の直交化 (GSO: Gram-Schmidt Orthonormalization)"
permalink: /snippets/gso
writer: anko9801
layout: library
---

## 説明




### Gram-Schmidt の直交化 (GSO: Gram-Schmidt Orthonormalization)

任意の $R$ ベクトル空間直交化
ベクトルをGSO化させることで任意の2つのベクトルの内積が0となる、つまり直交化できます。イメージは[Wikipedia](https://ja.wikipedia.org/wiki/%E3%82%B0%E3%83%A9%E3%83%A0%E3%83%BB%E3%82%B7%E3%83%A5%E3%83%9F%E3%83%83%E3%83%88%E3%81%AE%E6%AD%A3%E8%A6%8F%E7%9B%B4%E4%BA%A4%E5%8C%96%E6%B3%95)のgifがわかりやすいです。$\mathbf{b}_n$ の直交化は $\mathbf{b}_{1},\ldots, \mathbf{b}_{n-1}$ までと直行するように高さを保持しながら移動させる。

$$
\begin{aligned}
\begin{dcases}
\mathbf{b}_1^* = \mathbf{b}_1 \\
\mathbf{b}_i^* = \mathbf{b}_i - \sum\limits_{j=1}^{i-1} \mu_{i, j}\mathbf{b}_j^* \qquad \left( \mu_{i, j} = \frac{\langle \mathbf{b}_i, \mathbf{b}_j^* \rangle}{\| \mathbf{b}_j^* \|^2} \right) \\
\end{dcases}
\end{aligned}
$$

$$
\begin{aligned}
B &=
\begin{pmatrix}
\mathbf{b}_1 \\
\mathbf{b}_2 \\
\mathbf{b}_3 \\
\mathbf{b}_4 \\
\end{pmatrix}
& U &=
\begin{pmatrix}
1 & 0 & 0 & 0 \\
\mu_{2,1} & 1 & 0 & 0 \\
\mu_{3,1} & \mu_{3,2} & 1 & 0 \\
\mu_{4,1} & \mu_{4,2} & \mu_{4,3} & 1 \\
\end{pmatrix}
& B^* &=
\begin{pmatrix}
\mathbf{b}_1^* \\
\mathbf{b}_2^* \\
\mathbf{b}_3^* \\
\mathbf{b}_4^* \\
\end{pmatrix} \\
\end{aligned}
$$

$$
B = UB^*
$$

これらをGSOベクトル $\mathbf{b}_i^*$ , GSO係数 $\mu_{i, j}$ と呼びます。



## 計算量


## 実装

{% include python.html code="crypto/Lattice/LLL_reduction.sage" %}

## 使用例

## 参考
