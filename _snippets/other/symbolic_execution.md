---
title: "シンボリック実行エンジン"
permalink: /snippets/symbolic-execution
writer: anko9801
layout: library
---

## 説明

プログラム上で目的の地点に到達したいとき、それに当てはまるような入力値の条件を数学的に解くプログラム。条件分岐ごとに条件式を追加してそれをSMTソルバに解かせる。

## 計算量

条件分岐数を $N$ として $O(2^N)$

## 実装

レジスタ, メモリに関する制約とSSA形式のIRを条件式としてSMTソルバで解く。
- [mini_symbolic](https://github.com/anko9801/mini_symbolic)

## 使用例

シンボリック実行エンジンのプロジェクト angr のサンプルコード。

{% include python.html code="rev/rev.py" %}

## 参考

- [バイナリ萌えの彼女がシンボリック実行に恋着してますが、制約に挑む幼気な表情が最高です！（１）](https://speakerdeck.com/katc/bainarimeng-efalsebi-nu-gasinboritukushi-xing-nilian-zhao-sitemasuga-zhi-yue-nitiao-muyou-qi-nabiao-qing-gazui-gao-desu-1)
- [Girls Meets Symbolic Execution: Assertion 2. Automated Exploit Generation](https://speakerdeck.com/katc/girls-meets-symbolic-execution-assertion-2-automated-exploit-generation)
- [実装して学ぶ Symbolic Backward Execution](https://speakerdeck.com/katc/shi-zhuang-sitexue-bu-symbolic-backward-execution-aceefce8-d25e-4db0-8ebb-d648bb2c41cd)