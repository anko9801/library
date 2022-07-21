---
title: "ポテンシャル付きUnionFind"
permalink: /snippets/potential-unionfind
writer: anko9801
layout: library
---

## 説明

各頂点はポテンシャルを管理する。ポテンシャルの差がインターフェースとなる。重み付きUnionFindとも言う。

## 計算量

$O(\alpha(N))$

## 実装

{% include cpp.html code="data_structure/unionfind/potential_unionfind.hpp" %}

## 使用例

