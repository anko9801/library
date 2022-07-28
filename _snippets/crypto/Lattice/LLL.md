---
title: "LLL 基底簡約"
permalink: /snippets/lll
writer: anko9801
layout: library
---

## 説明

$n$ 次元格子 $L$ の基底 $\lbrace\mathbf{b_1},\ldots,\mathbf{b_n}\rbrace$ について以下の条件を満たすとき、その基底は LLL 簡約されている (Lenstra-Lenstra-Lovasz(LLL)-reduced)と呼ぶ。

1. 基底 $\lbrace\mathbf{b_1},\ldots,\mathbf{b_n}\rbrace$ がサイズ簡約されている。
2. Lovasz条件: 任意の $2 \leq k \leq n$ に対して
   $$
   \delta\|\mathbf{b}_{k-1}^*\| \leq \|\pi_{k-1}(\mathbf{b}_{k-1})\|
   $$
   を満たす。ただし、各 $1 \leq l \leq n$ に対して、$\pi_l$ は $\mathbb{R}$-ベクトル空間 $\langle\mathbf{b} _1,\ldots,\mathbf{b} _{l-1}\rangle _\mathbb{R}$ の直交補空間への直交射影とする。

これに対し、LLL 基底簡約アルゴリズムは次のように行う。

1. サイズ簡約する。
2. Lovasz条件を満たすように隣り合う基底ベクトルを交換する。

基底ベクトルを交換した際に GSO ベクトルも更新しなければならない。高速化出来る。

さらに LLL について精度を上げたり、機能を拡張することができ、DeepLLLやMLLLなどの手法がある。

- LLL は隣り合う基底ベクトルのみを比較するが、DeepLLL は全ての基底ベクトルを比較する。
- MLLL は一次従属なベクトルでも適用できる。

## 計算量


## 実装

{% include python.html code="crypto/Lattice/LLL_reduction.sage" %}

## 使用例

## 参考

