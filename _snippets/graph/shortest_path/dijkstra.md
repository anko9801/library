---
title: "単一始点最短路 (Dijkstra)"
permalink: /snippets/dijkstra
writer: anko9801
layout: library
---

## 説明

始点からの距離が全ての点の中で最小$\iff$最短距離が確定

## 計算量

$O(E\log{V})$

## 実装

{% include cpp.html code="graph/shortest_path/dijkstra.hpp" %}

## 使用例


