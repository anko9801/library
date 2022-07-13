---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

writer: anko9801
layout: page
---

superねこみみタイム

## データ構造

- UnionFind
  - [UnionFind](./posts/unionfind)
  - [ポテンシャル付きUnionFind](./posts/pot-unionfind)
- 平衡二分探索木
  - AVL木
  - 赤黒木
  - Splay木
  - Treap
- Wavelet Matrix
- [BIT(Binary-Indexed-Tree) / Fenwick Tree](./posts/fenwicktree)
- Segment Tree
  - [セグメント木](./posts/segment-tree)
  - [遅延セグメント木](./posts/lazy-segment-tree)
  - [Segment tree beats](./posts/segment-tree-beats)

## グラフ

- 最短路
  - [単一始点最短路 (Dijkstra)](./posts/dijkstra)
  - [単一始点最短路 (Bellman-Ford)](./posts/bellmanford)
  - k-最短路
  - 全点対間最短路 (Floyd Warshall)
  - 全点対間最短路 (Johnson)
- 全域木
  - [最小全域森 (Kruskal)](./posts/kruskal)
- フロー
  - [最大流 (Dinic)](./posts/dinic)
  - [最大流 (Ford Fulkerson)](./posts/ford-fulkerson)
- マッチング
  - [二部グラフ判定](./posts/bipartite)
  - [最大マッチング]()
- ツリー
  - [木の直径](./posts/double-sweep)
  - [最小共通祖先](./posts/lowest-common-ancestor)
- 最大クリーク
- 強連結成分分解

## アルゴリズム

- [二次元配列の回転](./posts/vector2d-rotate)
- [ランレングス圧縮](./posts/run-length-encode)
- [偏角ソート](./posts/arg-sort)
- [反復写像](./posts/iterated-function)
- [スライド最小値](./posts/slideminimum)
- [座標圧縮](./posts/compress)
- [最長増加部分列](./posts/lis)
- [ローリングハッシュ](./posts/rollinghash)

## 数学

- modulo
  - [Modint](./posts/modint)
  - [平方剰余 (Tonelli Shanks)]()
  - 離散対数問題
- 組合せ
  - [階乗](./posts/factorial)
  - [二項係数](./posts/binomial-coefficient)
- [形式的冪級数](./posts/fps)
- 進数変換
- [拡張ユークリッドの互除法](./posts/bezout-coef)
- 最大公約数/最小公倍数
- 中国剰余定理
- 行列演算
  - 行列
  - LU分解
  - 固有値・固有ベクトル
- 素数
  - [素因数分解 (線形篩)](./posts/sieve)
  - [高速素因数分解 (Pollard-$$\rho$$/Millar-Rabin)]()
  - [素数判定]()
  - [素数列挙 (エラトステネスの篩)]()
- [高速ゼータ変換/高速メビウス変換](./posts/zeta)
- [高速フーリエ変換(FFT)](./posts/fft)
- [数論変換(NTT)](./posts/ntt)
- [任意mod畳み込み]()
- 数論的関数
  - オイラーのφ関数
  - メビウスのμ関数
  - カーマイケルのλ関数
- 近似分数
- 格子
  - [LLL](./posts/lll)
- 多項式
  - [Coppersmith Method](./posts/coppersmith)
  - [グレブナー基底](./posts/grobner)
  - [終結式](./posts/resultant)
- 楕円曲線
  - ECDLP
  - Millarのアルゴリズム
  - Tate pairing / Weil pairing

## 幾何

- [幾何ライブラリ](./posts/geometry)

## 文字列

- [Z algorithm]()

## Pwn

- [Format String Attack]()
- GOT overwrite
- ret2xxx
  - ret2libc
- Return Oriented Programming
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

- RSA暗号
  - Wiener's Attack
  - Boneh-Durfee Attack
  - Common Modulus Attack
  - Håstad's Broadcast Attack
  - Small Common Private Exponent Attack
  - 適応的選択暗号文攻撃
  - LSB Decryption Oracle Attack
  - RSA-CRT Fault Attack
  - Franklin-Reiter Related Message Attack
  - Partial Key Exposure Attack
  - 逆元が存在しないとき
- 楕円曲線暗号
  - ECDLP
  - Polig-Hellman Attack
  - MOV Reduction
  - FR Reduction
  - SSSA Attack
  - Invalid Curve Attack
  - GHS Attack
  - Weil decsent
  - ECFFT

## テンプレート

- [競プロ](./posts/template)
- [ヒューリスティック](./posts/heuristic)
- [pwn](./posts/pwn)
- [angr](./posts/angr)