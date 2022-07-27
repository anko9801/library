---
writer: anko9801
layout: library
---

superねこみみタイム

これらはCC0ライセンスです。

<!-- {% assign mydocs = site.snippets | group_by: 'category' %}
{% for cat in mydocs %}

## {{ cat.name }}
{% assign items = cat.items | sort: 'title' %}{% for item in items %}
- [{{item.title}}]({{ item.url | relative_url }}){% endfor %}{% endfor %} -->

## データ構造

- UnionFind
  - [UnionFind](./snippets/unionfind)
  - [ポテンシャル付きUnionFind](./snippets/potential-unionfind)
  - [永続UnionFind](./snippets/persist-unionfind)
- [BIT (Binary-Indexed-Tree) / Fenwick Tree](./snippets/bit)
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
- 座標圧縮
- [slope trick](./snippets/slope-trick)

## グラフ

- 最短路
  - [単一始点最短路 $O(E\log V)$ (Dijkstra)](./snippets/dijkstra)
  - [単一始点最短路 $O(EV)$ (Bellman-Ford)](./snippets/bellman-ford)
  - k-最短路
  - [全点対間最短路 $O(V^3)$ (Floyd Warshall)](./snippets/floyd-warshall)
  - 全点対間最短路 $O((V + E)V\log V)$ (Johnson)
- 全域木
  - 最小全域森 (Kruskal)
- フロー
  - [最大流 (Dinic)](./snippets/dinic)
  - [最大流 (Ford Fulkerson)](./snippets/ford-fulkerson)
- マッチング
  - 二部グラフ判定
  - 最大マッチング
- ツリー
  - [木の直径](./snippets/tree-diameter)
  - 最小共通祖先
- 最大クリーク
- [強連結成分分解](./snippets/scc)

<!--
- [ランレングス圧縮](./snippets/run-length-encode)
- [反復写像](./snippets/iterated-function)
-->

## 数学

- modulo
  - [Modint](./snippets/modint)
  - [任意Modint](./snippets/arbitrary-modint)
  - sqrt (Tonelli Shanks)
- 進数変換
- [gcd / lcm / 拡張 Euclid の互除法](./snippets/gcd)
- [中国剰余定理](./snippets/crt)
- スライド最小値
- floor sum
- 行列演算
  - [行列](./snippets/matrix)
  - LU分解
  - 固有値・固有ベクトル
- 素数
  - [素因数分解](./snippets/factorize)
  - [高速素因数分解 (Pollard-$\rho$法/Millar-Rabin)](./snippets/fast-factorize)
  - 素数判定
  - [素数列挙 (エラトステネスの篩)](./snippets/primes)
- 多項式
  - 多項式GCD
- 形式的冪級数
- [高速ゼータ変換/高速メビウス変換](./snippets/zeta)
- [高速フーリエ変換(FFT)](./snippets/fft)
- [数論変換(NTT)](./snippets/ntt)
- 任意mod畳み込み
- 数論的関数
  - オイラーの$\phi$関数
  - メビウスの$\mu$関数
  - カーマイケルの$\lambda$関数

## 幾何

- [幾何ライブラリ](./snippets/geometry)
- 偏角ソート

## 文字列

- Z algorithm
- Rabin-Karp 法
- 最長増加部分列
- ローリングハッシュ
- Boyer-Moore
- LL(1) parser

## ヒューリスティック

- [山登り法](./snippets/hill-climbing)
- [焼きなまし法](./snippets/simulated-annealing)
- ビームサーチ
- chokudai サーチ
- Deep Learning

## Pwn

使用言語はPythonまたはC言語です。

- Format String Attack
- Stack Exploit
  - ret2xxx
    - ret2libc
  - Return Oriented Programming
- GOT overwrite
- Heap Exploit
  - glibc malloc
  - tcache poisoning
  - House of XXX
    - House of Orange
    - House of Spirit
    - House of Lore
    - House of Storm
    - House of Force
  - overlapping chunks
  - mmap overlapping chunks
- Kernel Exploit
  - Heap Spray
  - Dirty Pipe
- TEE
  - RISC-V Keystone
    - BOOM
    - Speculative Attack
  - Intel SGX
    - Remote Attestation
    - ForeShadow
  - ARM TrustZone
    - Boomerang

## Crypto

使用言語はPythonまたはSageMathです。それぞれの暗号自体を取り扱うのではなく、Cryptoの背景にある理論を取り扱っていきます。

- 暗号構成基盤
  - [Diffie-Hellman 鍵交換](./snippets/diffie-hellman)
  - [Schnorr Signatures](./snippets/schnorr)
- 格子
  - Gram-Schmidt
  - SVP (Shortest Vector Problem)
    - [Lagrange 基底簡約 (Gauss 基底簡約)](./snippets/lagrange)
    - [サイズ基底簡約](./snippets/size-reduction)
    - [LLL 基底簡約](./snippets/lll)
    - BKZ 基底簡約
    - Kannan’s embedding method
  - CVP (Closest Vector Problem)
    - Babai’s Algorithm
  - Merkle-Hellmanナップサック暗号
    - LO法
    - CLOS法
  - LWE (Learning with Errors) 暗号
    - LWE
      - BDD (Bounded Distance Decoding) 攻撃
      - SIS (Short Integer Solution) 攻撃
      - BKW 攻撃
      - Arora-Ge 攻撃
    - Ring-LWE
    - Module-LWE
      - CRYSTALS
    - LWR
  - TFHE (Torus Fully Homomorphic Encryption)
- 多項式
  - [Coppersmith Method](./snippets/coppersmith)
  - グレブナー基底
  - 終結式
  - MQ 問題
  - Matsumoto-Imai 暗号 / HFE 暗号
  - NTRU 暗号
  - Rainbow 署名 (UOV 署名 / QR-UOV 署名)
- [離散対数問題 (DLP)](./snippets/dlp)
  - [Baby-step Giant-step](./snippets/bsgs)
  - [Pollard's rho 法](./snippets/pollards-rho)
  - 指数計算法 (Index Calculus Algorithm)
  - 数体ふるい法
  - [Pohlig–Hellman](./snippets/pohlig-hellman)
- 数論
  - 二平方和
- RSA暗号
  - 構成
    - [RSA](./snippets/rsa)
    - RSA-CRT
  - 攻撃
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
  - Millarのアルゴリズム
  - Tate pairing / Weil pairing
  - ECFFT
- 楕円曲線暗号
  - 構成
    - ECDH
    - SIDH
    - SIKE
  - 攻撃
    - [Pohlig-Hellman Attack](./snippets/pohlig-hellman-ec)
    - MOV Reduction
    - FR Reduction
    - SSSA Attack
    - Invalid Curve Attack
    - GHS Attack
    - Weil decsent
- Hash
  - Merkle-Damgård construction
  - SHA (Secure Hash Algorithm)
  - MD5
- 疑似乱数生成器 (PRNG)
  - Xorshift
  - Mersenne twister

## Web

Webに関してはよわよわなので読み込みたい資料リストを並べます。

[CTFにおけるWebセキュリティ入門とまとめ](https://blog.hamayanhamayan.com/entry/2021/12/01/194114)

## その他

- 超解像
- Car Hacking
- Shell Oracle Attack
- Z3
  - シンボリック実行エンジン

## テンプレート

- [競プロ](./snippets/template)
- [ヒューリスティック](./snippets/heuristic)
- [pwn](./snippets/pwn)
- [angr](./snippets/angr)
- [SageMathチートシート](./snippets/sagemath)
