---
title: "Schnorr Signatures"
permalink: /snippets/schnorr
writer: anko9801
layout: library
---

## 説明

巡回群 $G$ 上で署名を行う。各パラメータは次のように定義する。

- 生成元 $g$
- 秘密鍵 $x$
- 公開鍵 $y = g^x$
- メッセージ $M$

### 署名

乱数 $k$ を生成し、次の値を計算する。

$$
\begin{aligned}
r &= g^k \\
e &= H(r \| M) \\
s &= k - xe
\end{aligned}
$$

このとき $(s, e)$ を署名値として公開する。

### 検証

公開されている値 $(g, y, M)$ と署名 $(s, e)$ を用いて次の値を計算する。

$$
\begin{aligned}
r' &= g^sy^e \\
e' &= H(r' \| M)
\end{aligned}
$$

ここで $e = e'$ となれば署名が有効であると検証されたことになる。