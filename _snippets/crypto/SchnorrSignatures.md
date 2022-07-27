---
title: "Schnorr Signatures"
permalink: /snippets/schnorr
writer: anko9801
layout: library
---

## 説明

非対話型ゼロ知識証明な署名の一種。

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

## 参考

- [Schnorr署名 ―― 30年の時を超えて注目を集める電子署名](https://blog.visvirial.com/articles/721)
- [RFC8235](https://datatracker.ietf.org/doc/html/rfc8235)