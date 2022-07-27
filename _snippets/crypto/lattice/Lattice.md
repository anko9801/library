---
title: "格子"
permalink: /snippets/lattice
writer: anko9801
layout: library
---

## 説明

### 格子 (Lattice)

図でイメージ掴むのが速い

線形独立な $n$ 個のベクトル $\mathbf{b}_1, \mathbf{b}_2, \ldots , \mathbf{b}_n \in \mathbb{R}^m$ について整数係数の線形結合によって生成されるベクトルの集合を格子 $L$ と定義します。

$$
L = \left\{ \sum_{i=0}^{n} a_i\mathbf{b}_i \ \middle| \ a_i \in \mathbb{Z} \right\}
$$

### Shortest Vector Problem(SVP)

格子上の非零なベクトルの中で最もノルムが小さなベクトルを見つけ出す問題です。
そのベクトルを $\mathbf{v}$ とおくと次のように表せられます。

$$
\mathbf{v} = v_1\mathbf{b}_1 + \ldots + v_n\mathbf{b}_n \qquad (\exists v_1, \ldots , v_n \in \mathbb{Z}) \\
$$

この問題はNP困難

#### 最短ベクトルの数え上げ

まずは全探索してみます。
考えてみると帰納的に求めるのでは正確な最短ベクトルは求められないでしょう。
考えてみるとある基底 $\mathbf{b}_i$ に対し、それ以下の基底 $\mathbf{b}_1, \ldots \mathbf{b}_{i-1}$ で組み立てられたベクトル $\mathbf{v}$ に対し、$\mathbf{b}_i$ を用いて短くする

効率的に数え上げる為には基底簡約すると良いということが知られています。


## 使用例

## 参考


