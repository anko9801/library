---
title: "Baby-step Giant-step"
permalink: /snippets/bsgs
writer: anko9801
layout: library
---

## 説明

半分全列挙を用いて $O(\sqrt{N}\log{N})$ でDLPが解ける。

位数 $N$ の巡回群 $G$ について命題 $\forall a, b\in G$, $\exists n\in \mathbb{N}$, $a^n = b$ を考える。このとき $m = \lceil\sqrt{N}\rceil$ とおき、$n$ を $m$ で割ると $n = qm + r \ (q, r\in[0, \lceil\sqrt{N}\rceil)\ )$ と表せられる。すると $r$ に対して $ba^{-r}$ を全列挙し、そのリストに対して $a^{qm}$ が含まれているような $q$ を探索すると高速に解が求まる。

例えば、有限体 $\mathbb{F}_q$ 上

楕円曲線 $E$ 上

## 計算量
$O(\sqrt{N}\log N)$

## 実装

## 使用例

## 参考
