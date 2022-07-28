---
title: "サイズ基底簡約"
permalink: /snippets/size-reduction
writer: anko9801
layout: library
---

## 説明

$n$ 次元格子 $L$ の基底 $\\{\mathbf{b_1},\ldots,\mathbf{b_n}\\}$ を GSO 係数 $\mu_{i,j}$ が

$$
|\mu_{i,j}| \leq \frac{1}{2} \quad (1 \leq \forall j < \forall i \leq n)
$$

を満たすとき、基底 $\\{\mathbf{b_1},\ldots,\mathbf{b_n}\\}$ はサイズ簡約されているという。

## 計算量


## 実装

{% include python.html code="crypto/Lattice/size_reduction.sage" %}

## 使用例

## 参考

