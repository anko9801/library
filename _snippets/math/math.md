---
title: "数学"
permalink: /snippets/math
writer: anko9801
layout: library
---

## 説明

## 計算量

## 実装

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T> T extgcd(T a, T b, T &x, T &y) {
  T d = a;
  if (b != 0) {
    d = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
  } else {
    x = 1;
    y = 0;
  }
  return d;
}

ll mod_inv(ll a, ll m) {
  ll x, y;
  extgcd(a, m, x, y);
  if (x < 0)
    x += m;
  return x;
}

ll garner(vector<ll> r, vector<ll> m) {
  int n = r.size();
  ll m_prod = 1;      // m_prod には m[i] の積を入れていく
  ll x = r[0] % m[0]; // 最初の条件を満たすような x の初期値
  if (n == 1)
    return x;
  for (int i = 1; i < n; i++) {
    m_prod *= m[i - 1]; // m の累積積を更新
    ll t = ((r[i] - x) * mod_inv(m_prod, m[i])) % m[i];
    if (t < 0)
      t += m[i];     // 負の数の剰余の対策
    x += t * m_prod; // x を更新
  }
  return x;
}
```

## 使用例
