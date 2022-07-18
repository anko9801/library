---
title: "素因数分解(線形篩)"
permalink: /snippets/sieve
writer: anko9801
layout: library
---

## 説明

init

- 整数$N$を与えると、前計算として$N$以下の合成数$i$について$i$の自明でない($1$でも$i$でもない)約数の1つを求める
- それと同時に、$N$以下の素数のリストも求める
- 以降の関数に$N$より大きい値を与えると補完のためにinitが呼ばれる。これは最初にinitに十分大きい値を与えることで回避できる
- 計算量は$Ο(N)$

linear_sieve

- コンストラクタ。initを呼ぶ

primearray

- 整数$N$を与えると、$N$以下の素数を昇順に並べたvectorを返す
- もし前計算が足りない場合、ちょうど補完するようにinitが実行される
- 計算量はinitのもの+$Ο(N/log(N))$

divisor

- 整数$N$を与えると、前計算した$N$の自明でない約数の1つを返す
- もし$N$が素数なら$N$を、$1$なら$1$を、正でないなら$-1$を返す
- もし前計算が足りない場合、ちょうど補完するようにinitが実行される
- 計算量はinitのもの+$Ο(1)$

factorization

- 整数$X$を与えると、$X$を素因数分解し、結果を**大きい順に**並べ、vectorとして返す
- もし前計算が足りない場合、ちょうど補完するようにinitが実行される
- 計算量はinitのもの+$Ο(log(N))$

exp_enum

- 整数$N,M,mod$を与えると、$0^M,1^M,...,N^M$をそれぞれ$mod$で割ったあまりを計算し、vectorとして返す
- $N,M$が負である場合、空のvectorを返す
- もし前計算が足りない場合、ちょうど補完するようにinitが実行される
- 計算量はinitのもの+$Ο(N + N \frac{log(M)}{log(N)})$

[github](https://github.com/0214sh7/procon-library/blob/master/math/linear%20sieve.cpp)

## 計算量


## 実装

```cpp
class linear_sieve{
    /*
    Copyright (c) 2021 0214sh7
    https://github.com/0214sh7/library/
    */

    private:
    long long S=0;
    std::vector<long long> divisor_,prime;

    public:
    void init(long long N){
        S=N;
        prime.clear();
        divisor_.resize(N+1);
        for(long long i=0;i<N+1;i++){
            divisor_[i]=0;
        }

        if(N>=1){
            divisor_[1]=1;
        }


        for(long long i=2;i<=N;i++){
            if(divisor_[i]==0){
                divisor_[i]=i;
                prime.push_back(i);
            }
            for(long long j=0;j<=prime.size() && prime[j]<=divisor_[i] && i*prime[j]<=N ;j++){
                divisor_[prime[j]*i]=prime[j];
            }
        }
    }

    linear_sieve(long long N){
        init(N);
    }

    std::vector<long long> primearray(long long X){
        std::vector<long long> R;
        if(X<=1)return R;
        if(S<X)init(X);
        for(long long i=0;i<prime.size();i++){
            if(prime[i]<=X){
                R.push_back(prime[i]);
            }
        }
        return R;
    }

    long long divisor(long long X){
        if(X<=0)return -1;
        if(S<X)init(X);
        return divisor_[X];
    }

    std::vector<long long> factorization(long long X){
        std::vector<long long> R;
        if(X<=1)return R;
        if(S<X)init(X);
        R = factorization(X/divisor_[X]);
        R.push_back(divisor_[X]);
        return R;
    }

    std::vector<long long> exp_enum(long long N,long long M,long long mod=LLONG_MAX){
        std::vector<long long> R;
        if(N<0 || M<0)return R;
        if(S<N)init(N);

        for(long long i=0;i<=N;i++){
            R.push_back(-1);
        }
        R[0]=0;
        if(N>=1)R[1]=1;

        for(long long i=0;i<prime.size();i++){
            if(prime[i]>N)continue;
            long long r=1,b=prime[i],e=M;
            while(e){
                if(e&1){
                    r=(r*b)%mod;
                }
                b=(b*b)%mod;
                e >>=1;
            }
            R[prime[i]]=r;
        }

        for(long long i=0;i<=N;i++){
            if(R[i]!=-1)continue;
            R[i] = (R[i/divisor_[i]]*R[divisor_[i]])%mod;
        }
        return R;
    }
};
```

## 使用例

***

### 実行コード

```cpp
#include <bits/stdc++.h>

class linear_sieve{/*省略*/};

int main(void){

    linear_sieve sieve(1000);

    std::cout << "100以下の素数のリスト" << std::endl;
    std::vector<long long> P = sieve.primearray(100);
    for(int i=0;i<P.size();i++){
        std::cout << P[i] << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "1~10の約数の一つ" << std::endl;
    for(int i=1;i<=10;i++){
        std::cout << sieve.divisor(i) << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "4,12,57,97,210の素因数分解" << std::endl;
    std::vector<long long> number={4,12,57,97,210};
    for(int j=0;j<5;j++){
        std::vector<long long> F = sieve.factorization(number[j]);
        for(int i=0;i<F.size();i++){
            std::cout << F[i] << " ";
        }std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "0~10について、i^3" << std::endl;
    std::vector<long long> E = sieve.exp_enum(10,3);
    for(int i=0;i<E.size();i++){
        std::cout << E[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 出力

```text
100以下の素数のリスト
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97

1~10の約数の一つ
1 2 3 2 5 2 7 2 3 2

4,12,57,97,210の素因数分解
2 2
3 2 2
19 3
97
7 5 3 2

0~10について、i^3
0 1 8 27 64 125 216 343 512 729 1000
```

## 更新履歴

***

| 日時 | 内容 |
| :---: | :--- |
| 2021/03/24 | 素因数分解(線形篩)を追加 |
