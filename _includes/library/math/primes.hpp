#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
using ll = long long;

vector<ll> primes;

vector<bool> Eratosthenes(int N) {
  vector<bool> isprime(N + 1, true);
  isprime[0] = isprime[1] = false;

  for (int p = 2; p <= N; ++p) {
    if (!isprime[p])
      continue;
    primes.push_back(p);
    for (int q = p * 2; q <= N; q += p) {
      isprime[q] = false;
    }
  }
  return isprime;
}

vector<ll> factors(ll N) {
  vector<ll> res;
  for (long long a = 2; a * a <= N; ++a) {
    if (N % a != 0)
      continue;
    long long ex = 0; // 指数

    // 割れる限り割り続ける
    while (N % a == 0) {
      ++ex;
      N /= a;
    }

    // その結果を push
    res.push_back(a);
  }
  if (N != 1)
    res.push_back(N);
  return res;
}