---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

writer: anko9801
layout: library
---

superねこみみタイム

<!-- {% assign mydocs = site.snippets | group_by: 'category' %}
{% for cat in mydocs %}

## {{ cat.name }}
{% assign items = cat.items | sort: 'title' %}{% for item in items %}
- [{{item.title}}]({{ item.url | relative_url }}){% endfor %}{% endfor %} -->

## データ構造

- UnionFind
  - [UnionFind](./snippets/unionfind)
  - [ポテンシャル付きUnionFind](./snippets/pot-unionfind)
- [BIT (Binary-Indexed-Tree) / Fenwick Tree](./snippets/fenwicktree)
- Segment Tree
  - [セグメント木](./snippets/segtree)
  - [遅延セグメント木](./snippets/lazysegtree)
  - [Segment tree beats](./snippets/segtreebeats)
- 平衡二分探索木
  - AVL木
  - 赤黒木
  - Splay木
  - Treap
- Wavelet Matrix

## グラフ

- 最短路
  - [単一始点最短路 (Dijkstra)](./snippets/dijkstra)
  - [単一始点最短路 (Bellman-Ford)](./snippets/bellmanford)
  - k-最短路
  - 全点対間最短路 (Floyd Warshall)
  - 全点対間最短路 (Johnson)
- 全域木
  - [最小全域森 (Kruskal)](./snippets/kruskal)
- フロー
  - [最大流 (Dinic)](./snippets/dinic)
  - [最大流 (Ford Fulkerson)](./snippets/ford-fulkerson)
- マッチング
  - [二部グラフ判定](./snippets/bipartite)
  - [最大マッチング]()
- ツリー
  - [木の直径](./snippets/double-sweep)
  - [最小共通祖先](./snippets/lowest-common-ancestor)
- 最大クリーク
- 強連結成分分解

## アルゴリズム

- [二次元配列の回転](./snippets/vector2d-rotate)
- [ランレングス圧縮](./snippets/run-length-encode)
- [偏角ソート](./snippets/arg-sort)
- [反復写像](./snippets/iterated-function)
- [スライド最小値](./snippets/slideminimum)
- [座標圧縮](./snippets/compress)

## 数学

- modulo
  - [Modint](./snippets/modint)
  - [任意Modint](./snippets/arbitrary-modint)
  - [平方剰余 (Tonelli Shanks)]()
  - 離散対数問題
- 組合せ
  - [階乗](./snippets/factorial)
  - [二項係数](./snippets/binomial-coefficient)
- [形式的冪級数](./snippets/fps)
- Half GCD
- 進数変換
- [Euclid の互除法](./snippets/bezout-coef)
- 最大公約数/最小公倍数
- 中国剰余定理
- 行列演算
  - 行列
  - LU分解
  - 固有値・固有ベクトル
- 素数
  - [素因数分解 (線形篩)](./snippets/sieve)
  - [高速素因数分解 (Pollard-$$\rho$$法/Millar-Rabin)]()
  - [素数判定]()
  - [素数列挙 (エラトステネスの篩)]()
- [高速ゼータ変換/高速メビウス変換](./snippets/zeta)
- [高速フーリエ変換(FFT)](./snippets/fft)
- [数論変換(NTT)](./snippets/ntt)
- [任意mod畳み込み]()
- 数論的関数
  - オイラーの$$\phi$$関数
  - メビウスの$$\mu$$関数
  - カーマイケルの$$\lambda$$関数

## 幾何

- [幾何ライブラリ](./snippets/geometry)

## 文字列

- [Z algorithm]()
- [最長増加部分列](./snippets/lis)
- [ローリングハッシュ](./snippets/rollinghash)
- Boyer-Moore
- LL1 parser

## Pwn

使用言語はPythonまたはC言語です。

- [Format String Attack]()
- Stack Exploit
  - ret2xxx
    - ret2libc
  - Return Oriented Programming
- GOT overwrite
- Heap Exploit
  - [tcache poisoning]()
  - Heap Spray
  - House of XXX
    - [House of Orange]()
    - [House of Spirit]()
    - [House of Lore]()
    - [House of Storm]()
    - [House of Force]()
  - [overlapping chunks]()
  - [mmap overlapping chunks]()
- Kernel Exploit
  - []()

## Crypto

使用言語はPythonまたはSageMathです。

- ディオファントス近似
- 格子
  - [LLL](./snippets/lll)
  - BKS
- 多項式
  - [Coppersmith Method](./snippets/coppersmith)
  - [グレブナー基底](./snippets/grobner)
  - [終結式](./snippets/resultant)
- RSA暗号
  - [Wiener's Attack](./snippets/wieners-attack)
  - [Boneh-Durfee Attack](./snippets/boneh-durfee)
  - [Common Modulus Attack](./snippets/common-modulus)
  - [Håstad's Broadcast Attack](./snippets/hastads-broadcast)
  - [Small Common Private Exponent Attack](./snippets/small-private-exponent)
  - [適応的選択暗号文攻撃](./snippets/rsa-cca)
  - [LSB Decryption Oracle Attack](./snippets/lsb-decryption-oracle)
  - [RSA-CRT Fault Attack](./snippets/rsa-crt-fault)
  - [Franklin-Reiter Related Message Attack](./snippets/franklin-reiter)
  - [Partial Key Exposure Attack](./snippets/partial-key)
  - [逆元が存在しないとき](./snippets/no-inverse)
- 楕円曲線
  - ECDLP
  - Millarのアルゴリズム
  - Tate pairing / Weil pairing
  - ECFFT
- 楕円曲線暗号
  - Polig-Hellman Attack
  - MOV Reduction
  - FR Reduction
  - SSSA Attack
  - Invalid Curve Attack
  - GHS Attack
  - Weil decsent

## テンプレート

- [競プロ](./snippets/template)
- [ヒューリスティック](./snippets/heuristic)
- [pwn](./snippets/pwn)
- [angr](./snippets/angr)