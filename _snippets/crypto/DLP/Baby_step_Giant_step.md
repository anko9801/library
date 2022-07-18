---
title: "Baby-step Giant-step"
permalink: /snippets/bsgs
writer: anko9801
layout: library
---

## 説明

半分全列挙を用いて $O(\sqrt{N})$ でDLPを解ける。

巡回群 $G$ について
有限体 $\mathbb{F}_p$ について $m = \lceil \sqrt{p-1} \rceil$ とおき、$x$ を $m$ で割った商と余りを $q, r$ として次の集合 $B, G$ について考える。
$x = qm + r$

$$
\begin{aligned}
y &= g^x \\
y &= g^{qm+r} \\
yg^{-r} &= (g^m)^q \\
\end{aligned}
$$

$$
\begin{aligned}
y &= g^x \\
y &= g^{qm+r} \\
yg^{-r} &= (g^m)^q \\
B &= \{ yg^{-r} \mid 0 \leq r < m\} \\
G &= \{ g^{mq} \mid 0 \leq q < m\}
\end{aligned}
$$

まず集合 $B$ を構築し、集合 $G$ を1つずつ集合 $B$ に対して検索に掛け、存在したとき $x = qm + r$ とすることでDLPの解が求まります。

楕円曲線 $E$ でも同様に $m = \lceil \sqrt{\#P} \rceil$ として集合 $B, G$  を考えれば解けます。

$$
\begin{aligned}
Q &= dP \\
Q &= (qm + r)P \\
Q - rP &= q(mP) \\
B &= \{ Q - rP \mid 0 \leq r < m \} \\
G &= \{ qmP \mid 0 \leq q < m \}
\end{aligned}
$$

これより計算量は位数 $n$ を用いて $O(\sqrt{n}\log n)$ メモリ空間は $O(\sqrt{n})$ だけ必要となります。

## 実装

## 使用例

## 参考
