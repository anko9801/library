---
title: "UnionFind"
permalink: /snippets/unionfind
writer: anko9801
layout: library
---

## 説明

素集合を管理するデータ構造。2つの工夫を用いてより高速にできる。
- 経路圧縮
  再帰的に根を調べる際に根に直接つなぎ直す
- ランク
  マージする際にランクの小さい方を大きい方へ繋げる

## 計算量

工夫をどちらか実装していれば $O(\log{N})$
どちらも実装していれば $O(\alpha(N))$

## 実装

{% include cpp.html code="data_structure/unionfind/unionfind.hpp" %}

## 使用例

