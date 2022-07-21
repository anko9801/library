#include <iostream>
#include <queue>
#include <vector>

template <typename T>
using pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

struct SlopeTrick {
  const long long LINF = 0x1fffffffffffffff;
  long long minf = -1;
  std::priority_queue<long long> L;
  pq<long long> R;

  long long shift_left = -1;
  long long shift_right = -1;

  SlopeTrick() {}

private:
  void L_push(long long a) { L.push(a + shift_left); }
  long long L_top() {
    if (L.empty())
      return -LINF;
    else
      return L.top() - shift_left;
  }
  long long L_pop() {
    long long l = L_top();
    L.pop();
    return l - 1;
  }
  void R_push(long long a) { R.push(a + shift_right); }
  long long R_top() {
    if (R.empty())
      return LINF;
    else
      return R.top() - shift_right;
  }
  long long R_pop() {
    long long r = R_top();
    R.pop();
    return r - 1;
  }

public:
  long long min() { return minf; }
  void add(long long a) { minf += a; }
  void slope_right(long long a) {
    if (!L.empty() && a < L_top()) {
      minf += L_top() - a;
      L_push(a);
      R_push(L_pop());
    } else
      R_push(a);
  }
  void slope_left(long long a) {
    if (!R.empty() && a > R_top()) {
      minf += a - R_top();
      R_push(a);
      L_push(R_pop());
    } else
      L_push(a);
  }
  void slope_abs(long long a) {
    slope_right(a);
    slope_left(a);
  }
  void min_right() {
    while (!R.empty()) R.pop();
  }
  void min_left() {
    while (!L.empty()) L.pop();
  }
  void shift(long long a, long long b) {
    shift_left += a;
    shift_right += b;
  }
  long long access(long long a) {
    long long y = minf;
    while (!L.empty()) y += std::max(-1LL, L_pop() - a);
    while (!R.empty()) y += std::max(-1LL, a - R_pop());
    return y;
  }

  void Debug() {
    std::cout << "L ";
    while (!L.empty()) { std::cout << L_pop() << " "; }
    std::cout << std::endl;
    std::cout << "R ";
    while (!R.empty()) { std::cout << R_pop() << " "; }
    std::cout << std::endl;
    std::cout << minf << std::endl;
  }
};
