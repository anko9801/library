---
title: "ハッシュ関数"
permalink: /snippets/hash
writer: anko9801
layout: library
---

## 説明

- 原像計算困難性 与えられた $h$ に対して $H(m) = h$ となる $m$ を見つけることが困難である．
- 第二原像計算困難性 $m1$ が与えられたときに $H(m1) = H(m2)$ となる $m2(̸= m1)$ を求めるのが困難である．
- 衝突困難性 相異なる $m1$ と $m2$ で，$H(m1) = H(m2)$ となるメッセージを見つけることが困難である．

HMAC (Hash-based MAC)

伸長攻撃
- Merkle-Damgård construction