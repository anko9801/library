---
title: "単一始点最短路 (Bellman-Ford)"
permalink: /snippets/bellman-ford
writer: anko9801
layout: library
---

## 説明

全ての辺を更新できなくなるまで更新する。
$V$回目のループで更新が発生するなら負閉路が存在する。

## 計算量

$O(EV)$

## 実装

{% include cpp.html code="graph/shortest_path/bellman_ford.hpp" %}

## 使用例

