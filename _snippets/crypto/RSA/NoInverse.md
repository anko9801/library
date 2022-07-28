---
title: "逆元が存在しないとき"
permalink: /snippets/no-inverse
writer: anko9801
layout: library
---

## 説明

乗法群の位数が $\phi(N) = se^n = 0 \pmod e$ のとき $e$ の逆元が取れない。このとき、位数 $s$ の乗法群に落として逆元を取り、位数 $se^n$ の元を $e^n$ 回掛けて全探索すると平文が見つかる。

## 計算量

$O(e^n)$

## 実装


## 使用例


## 参考

[p - 1 ≡ 0 (mod e) のときの RSA 復号方法](https://blog.y011d4.com/20201026-not-coprime-e-phi)
