#include <vector>

std::vector<int> primes;
std::vector<bool> Eratosthenes(int N) {
  std::vector<bool> isprime(N + 1, true);
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
