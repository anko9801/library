---
title: "メルセンヌ ツイスタ"
permalink: /snippets/mersenne-twister
writer: anko9801
layout: library
---

## 説明

長い周期 $2^{19937}-1$ を持つ疑似乱数生成器。連続した624回の32ビット出力から内部状態を復元できてしまう。
2つの値で十分のときもあるらしい
https://www.ambionics.io/blog/php-mt-rand-prediction

## 参考

- [メルセンヌ・ツイスタをわかった気になる](https://6715.jp/posts/5/)
- [Mersenne Twisterの出力を推測してみる](https://inaz2.hatenablog.com/entry/2016/03/07/194147)