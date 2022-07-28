---
title: "高速素因数分解 (Pollard-ρ法/Miller-Rabin法)"
permalink: /snippets/fast-factorize
writer: anko9801
layout: library
---

## 説明

Pollard-$\rho$ 法と Miller-Rabin 法を用いて $O(n^{\frac{1}{4}}\log^3n)$ で素因数分解できる。

### Miller–Rabin 素数判定法

Miller-Rabin 素数判定法は与えられた数 $n$ が素数かどうかを計算時間 $O(k\log^3 n)$ で誤り率 $4^{-k}$ 以下で判定する確率的素数判定アルゴリズムである。

フェルマーの小定理について考える。素数である剰余 $n$ について、その乗法群の位数 $n-1$ はそれを $2$ で割れるだけ割った数を $d$ として $n-1 = 2^sd$ と書ける。

$$
\begin{aligned}
a^{n-1} &= a^{2^sd} ≡ 1 \quad \pmod n \\
a^{2^sd}-1 &= (a^d-1)(a^d+1)(a^{2d}+1)(a^{4d}+1)\cdots(a^{2^{s-1}d}+1)\\
&≡ 0 \\
\iff&\begin{cases}
a^d &≡ 1 & \pmod n \\
a^{2^rd} &≡ -1 & \pmod n & (\exists r \in \mathbb{Z}, 0\leq r\leq s-1)
\end{cases}
\end{aligned}
$$

この対偶をとると、「次の2式を満たす $a$ が存在するならば

$$
\begin{aligned}
\begin{cases}
a^d &\neq 1 & \pmod n \\
a^{2^rd} &\neq -1 & \pmod n & (\forall r \in \mathbb{Z}, 0\leq r\leq s-1)
\end{cases}
\end{aligned}
$$

$n$ は合成数である」と言える。

これを用い、次のステップを実行することで確率的な素数判定ができる。

1. ランダムに $a \in [1, n-1]$ をとってくる
2. 上の条件を満たしたら composite と返す
3. 満たさなければ probably prime と返す

これを繰り返すことで判定の精度が高まります。この処理をMiller–Rabin素数判定法と呼びます。

2, 325, 9375, 28178, 450775, 9780504, 1795265022

## 計算量

$O(k\log^3 n)$ 、FFTベースの乗算を用いると $Õ(k\log^2 n)$

## 実装

## 使用例

## 参考
[Deterministic variants of the Miller-Rabin primality test](http://miller-rabin.appspot.com/)
