---
title: "数論変換"
permalink: /snippets/ntt
writer: anko9801
layout: library
---

## 説明

複素数上のFFTを有限体上に取り替えたのがNTT。乗法群の位数が大きな2のべき乗を持っていると精度を落とさずに計算できて嬉しい。

## 計算量

$O(N\log{N})$

## 実装

{% include cpp.html code="math/ntt.hpp" %}

## 使用例
