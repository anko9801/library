---
title: "Lagrange 基底簡約 (Gauss 基底簡約)"
permalink: /snippets/lagrange
writer: anko9801
layout: library
---

## 説明

任意の $q \in \mathbb{Z}$ に対して

$$
\|\mathbf{b}_1\| \leq \|\mathbf{b}_2\| \leq \|\mathbf{b}_1 + q\mathbf{b}_2\|
$$

を満たすとき、2次元格子の基底 $\\{\mathbf{b}_1, \mathbf{b}_2\\}$ はLagrange 簡約されているという。

Euclidの互除法を2次元格子に対して行うことで Lagrange 簡約されているような基底を生み出せる。

## 計算量

$O(\log{N})$


## 実装

{% include python.html code="crypto/Lattice/lagrange.sage" %}

## 使用例

## 参考
