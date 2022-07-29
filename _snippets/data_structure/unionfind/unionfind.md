---
title: "UnionFind"
permalink: /snippets/unionfind
writer: anko9801
layout: library
---

## 説明

素集合を管理するデータ構造。

以下の工夫により高速化できる。

- 経路圧縮 (path compression)
  再帰的に根を調べる際に根に直接つなぎ直す
- 併合の工夫
  併合時に木の高さ/大きさが小さい方を大きい方へ繋げる
  union by rank: 木の高さ
  union by size: 木の大きさ

## 計算量

経路圧縮のみ $O(\log{N})$
併合の工夫のみ $O(\log{N})$
両方 $O(\alpha(N))$

## 実装

{% include cpp.html code="data_structure/unionfind/unionfind.hpp" %}

## 使用例

