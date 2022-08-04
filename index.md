---
writer: anko9801
layout: library
---

superねこみみタイム

# これはなに？

CTFのライブラリ/知識集らしいです。(現在はLYTに近い思想で書いてる)

競プロはライブラリ化されたものがよく出回ってるけど、CTFの方はほとんど閉じた場所でしか共有されてないよな～と思ったのであんこ(将来的にtraPのCTF班)がCTFに関するライブラリやCTFに必要な知識をまとめたものです。編集したい方は大歓迎です！気軽にプルリク投げてください～

これらはCC0ライセンスとします。自由にコピペしてOKです！

## データ構造

- UnionFind
  - [UnionFind](./snippets/unionfind)
  - [ポテンシャル付きUnionFind](./snippets/potential-unionfind)
  - [永続UnionFind](./snippets/persist-unionfind)
- [BIT (Binary-Indexed-Tree) / Fenwick Tree](./snippets/bit)
- Segment Tree
  - [セグメント木](./snippets/segtree)
  - [遅延セグメント木](./snippets/lazysegtree)
  - [Segment Tree Beats](./snippets/segtreebeats)
- 平衡二分探索木
  - 赤黒木
  - AVL木
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
  - 行列木定理
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
- [高速ゼータ変換/高速メビウス変換](./snippets/zeta)
- [高速フーリエ変換(FFT)](./snippets/fft)
- [数論変換(NTT)](./snippets/ntt)
- 多項式GCD
- 形式的冪級数
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
- [ビームサーチ](./snippets/beam-search)
- [chokudai サーチ](./snippets/chokudai-search)

## Pwn

使用言語はPythonまたはC言語です。

- Format String Attack
- Stack Exploit
  - ret2xxx
    - ret2libc
  - ROP: Return Oriented Programming
- GOT overwrite
- Heap Exploit
  - glibc malloc
  - tcache poisoning
  - tcache double free
  - fastbin attack
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

## Crypto

使用言語はPythonまたはSageMathです。それぞれの暗号自体を取り扱うのではなく、Cryptoの背景にある理論を取り扱っていきます。

- 暗号構成基盤
  - [Diffie-Hellman 鍵交換](./snippets/diffie-hellman)
  - Fiat-Shamir 変換
    - [Schnorr 署名](./snippets/schnorr)
    - Frozen Heart
  - Lamport 署名
  - ゼロ知識証明
- 格子
  - Gram-Schmidt
  - SVP (Shortest Vector Problem)
    - [Lagrange 基底簡約 (Gauss 基底簡約)](./snippets/lagrange)
    - [サイズ基底簡約](./snippets/size-reduction)
    - [LLL 基底簡約](./snippets/lll)
    - BKZ 基底簡約 / HKZ 基底簡約
    - Kannan’s embedding method
  - CVP (Closest Vector Problem)
    - Babai’s Algorithm
  - Merkle-Hellmanナップサック暗号
    - LO法
    - CLOS法
  - LWE (Learning with Errors) 暗号
    - LWE
      - BDD (Bounded Distance Decoding) Attack
      - SIS (Short Integer Solution) Attack
      - BKW Attack
      - Arora-Ge Attack
    - Ring-LWE
    - Module-LWE
      - CRYSTALS
    - LWR
  - [TFHE (Torus Fully Homomorphic Encryption)](./snippets/tfhe)
- 多項式
  - [Coppersmith Method](./snippets/coppersmith)
  - グレブナー基底
  - 終結式
  - MQ 問題
  - Matsumoto-Imai 暗号 / HFE 暗号
  - NTRU 暗号
  - Rainbow 署名
  - UOV 署名 / QR-UOV 署名
- 数論
  - 二平方和
  - [離散対数問題 (DLP)](./snippets/dlp)
    - [Baby-step Giant-step](./snippets/bsgs)
    - [Pollard's rho 法](./snippets/pollards-rho)
    - 指数計算法 (Index Calculus Algorithm)
    - 数体ふるい法
    - [Pohlig–Hellman](./snippets/pohlig-hellman)
- [RSA暗号](./snippets/rsa)
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
- 楕円曲線暗号
  - 楕円曲線
    - Millar のアルゴリズム
    - Schoof のアルゴリズム
    - Tate pairing / Weil pairing
    - ECFFT
    - Fujisaki-Okamoto Transformation
    - 超楕円曲線
  - 攻撃
    - [Pohlig-Hellman Attack](./snippets/pohlig-hellman-ec)
    - MOV Reduction
    - FR Reduction
    - SSSA Attack
    - Invalid Curve Attack
    - GHS Attack
    - Weil decsent
    - Dual EC DRBG
- AES
  - Padding Oracle Attack
  - BEAST Attack
  - Lucky Thirteen Attack
  - POODLE Attack
  - ghash
  - Integral Cryptanalysis
- Hash
  - 誕生日攻撃
- 疑似乱数生成器 (PRNG)
  - Xorshift
  - [Mersenne twister](./snippets/mersenne-twister)
- ブロックチェーン
  - Flash Loan Attack

## Web

Webに関してはよわよわなので読み込むと良いかもしれない資料リストを集めています。(これ読むといいよみたいなのがあったら教えてくださると助かります！)

- [CTFにおけるWebセキュリティ入門とまとめ](https://blog.hamayanhamayan.com/entry/2021/12/01/194114)
- 常設Web問
  - [Web Security Academy](https://portswigger.net/web-security/all-labs)
  - [KENRO](https://kenro.flatt.tech)
  - [wargame.kr](http://wargame.kr)
  - [XSS Game](https://xss-game.appspot.com)
  - [The Lord of the SQLI](https://los.rubiya.kr)
- [SQL Injection list](https://github.com/payloadbox/sql-injection-payload-list)

## 量子アルゴリズム

- 各ゲートの紹介と量子計算の方法
- Shor のアルゴリズム
- 量子暗号通信
- 量子中継ネットワーク

## 構造探検隊

- ELF
- JPEG
- FAT32
- ZIP

## 電子回路

- SDR
- SPI
- JTAG

## 脆弱性集

- [CVEs for the Rust standard library](https://rustrepo.com/repo/Qwaz-rust-cve-rust-security-tools)
  - [Rustのunsound hole issue #25860を理解する](https://speakerdeck.com/moratorium08/rustfalseunsound-hole-issue-number-25860woli-jie-suru)
  - [str::repeat - stable wildcopy exploit](https://saaramar.github.io/str_repeat_exploit/)

## 雑学

- ピッキング
- Tamper Evident
- Social Engineering
- Car Hacking
- 航空技術
- CPU / GPU
  - Spectre / Meltdown
- bit trick
  - XOR swap
- 仮想化技術
  - [ハイパーバイザの作り方](https://syuu1228.github.io/howto_implement_hypervisor/)
- プログラミング言語
- 未定義動作
- デバッガ
- データベース
- ネットワーク構成
- Z3
  - [シンボリック実行エンジン](./snippets/symbolic-execution)
- 定理証明支援系
- Deep Learning
  - 超解像

## テンプレート

- [競プロ](./snippets/template)
- [ヒューリスティック](./snippets/heuristic)
- [pwn](./snippets/pwn)
- Kernel exploit
- [SageMathチートシート](./snippets/sagemath)
