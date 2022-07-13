#include <bits/stdc++.h>
using namespace std;
// using namespace atcoder;
using ll = long long;
using ld = long double;
using uint = unsigned;
using ull = unsigned long long;

using Real = long double;

const Real EPS = 1e-9;
const Real PI = 3.1415926535897932;
inline bool equal(const Real &a, const Real &b) { return fabs(a - b) < EPS; }
Real radian_to_degree(const Real &r) { return r * 180.0 / PI; }
Real degree_to_radian(const Real &d) { return d * PI / 180.0; }

using Point = complex<Real>;

istream &operator>>(istream &is, Point &p) {
  Real a, b;
  is >> a >> b;
  p = Point(a, b);
  return is;
}
ostream &operator<<(ostream &os, Point &p) {
  return os << fixed << setprecision(10) << p.real() << " " << p.imag();
}

// 点 p を反時計回りに theta 度回転
Point rotate(const Point &p, const Real &theta) {
  return Point(cos(theta) * p.real() - sin(theta) * p.imag(),
               sin(theta) * p.real() + cos(theta) * p.imag());
}

struct Line {
  Point a, b;
  Line() = default;
  Line(Point a, Point b) : a(a), b(b) {}

  // Ax+By=C
  Line(Real A, Real B, Real C) {
    if (equal(A, 0))
      a = Point(0, C / B), b = Point(1, C / B);
    else if (equal(B, 0))
      b = Point(C / A, 0), b = Point(C / A, 1);
    else
      a = Point(0, C / B), b = Point(C / A, 0);
  }

  friend ostream &operator<<(ostream &os, Line &p) {
    return os << p.a << " to " << p.b;
  }
  friend istream &operator>>(istream &is, Line &a) { return is >> a.a >> a.b; }
};

struct Segment : Line {
  Segment() = default;
  Segment(Point a, Point b) : Line(a, b) {}
};

struct Circle {
  Point p;
  Real r;

  Circle() = default;
  Circle(Point p, Real r) : p(p), r(r) {}
};

using Points = vector<Point>;
using Polygon = vector<Point>;
using Segments = vector<Segment>;
using Lines = vector<Line>;
using Circles = vector<Circle>;

Real dot(const Point &a, const Point &b) {
  return (a.real() * b.real() + a.imag() * b.imag());
}

Real cross(const Point &a, const Point &b) {
  return (a.real() * b.imag() - a.imag() * b.real());
}

// 点の回転方向
static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;
int ccw(Point p0, Point p1, Point p2) {
  Point a = p1 - p0, b = p2 - p0;
  if (cross(a, b) > EPS)
    return COUNTER_CLOCKWISE;
  if (cross(a, b) < -EPS)
    return CLOCKWISE;
  if (dot(a, b) < -EPS)
    return ONLINE_BACK;
  if (norm(a) < norm(b))
    return ONLINE_FRONT;
  return ON_SEGMENT;
}

bool parallel(const Line &a, const Line &b) {
  return equal(cross(a.b - a.a, b.b - b.a), 0.0);
}

bool orthogonal(const Line &a, const Line &b) {
  return equal(dot(a.b - a.a, b.b - b.a), 0.0);
}

// 射影(projection)
// 直線(線分)lに点pから引いた垂線の足を求める
Point projection(const Line &l, const Point &p) {
  Real t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + (l.a - l.b) * t;
}

Point projection(const Segment &l, const Point &p) {
  Real t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + (l.a - l.b) * t;
}

// 反射(reflection)
// 直線lを対称軸として点pと線対称の位置にある点を求める
Point reflection(const Line &l, const Point &p) {
  return p + (projection(l, p) - p) * 2.0L;
}

// 線分sと線分tが交差しているかどうか
bool isIntersect(const Segment &s, const Segment &t) {
  return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 &&
         ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

int isIntersect(const Circle &c1, const Circle &c2) {
  Real d = norm(c1.p - c2.p);
  // 2つの円が離れている場合
  if (d > norm(c1.r + c2.r) + EPS)
    return 4;
  // 外接している場合
  if (equal(d, norm(c1.r + c2.r)))
    return 3;
  // 内接している場合
  if (equal(d, norm(c1.r - c2.r)))
    return 1;
  // 内包している場合
  if (d < norm(c1.r - c2.r) - EPS)
    return 0;
  // 交差している場合
  return 2;
}