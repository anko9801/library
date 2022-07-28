---
title: "Chosen-ciphertext Attack"
permalink: /snippets/rsa-cca
writer: anko9801
layout: library
---

## 説明

任意の暗号を復号した結果を知っているとき、ある暗号文の復号結果を防がれていたとしても他の暗号を送ることで解読できます。
$2^e$ を暗号文に掛けて復号した結果を $2$ で割ればその平文がわかります。

$$
\begin{aligned}
Dec(2^ec) = 2m \pmod N
\end{aligned}
$$

これに対する防御方法として平文にパディングを施し、復号化した際にパディング形式が違うときは相手に渡さないようにするという方法があります。これによって正当な暗号文しか受け入れず、適応的選択暗号文攻撃を防げます。

パディング形式の1つにPKCS #1 v1.5があります。

`0002<random>00<hashprefix><message>`

これについてパディングが合っているかどうかを相手に送ってしまうとPadding Oracle Attackで攻撃でき、PKCS #1 v1.5では200万程度送ると平文が読めてしまいます。

対してPadding Oracle Attackで破られないようなパディング形式はInD-CCA2と呼びます。

その1つであるOAEP(Optimal Asymmetric Encryption Padding)については次の記事を読むとよいです。

## 実装


## 使用例


## 参考

- [RSAに対する適応的選択暗号文攻撃とパディング方式](https://inaz2.hatenablog.com/entry/2016/01/26/222303)
