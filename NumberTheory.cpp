#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = uint_fast64_t;
using pll = pair<ll, ll>;
using i64 = int_fast64_t;
using u64 = uint_fast64_t;

const ll MOD = 1e9+7;
const ll MODD = 998244353;

ll gcd(ll a, ll b) { if (b) return gcd(b, a % b); return a; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
ll extgcd(ll a, ll b, ll &x, ll &y) {
	ll g = a; x = 1; y = 0;
	if (b) {
		g = extgcd(b, a % b, y, x);
		y -= a / b * x;
	}
	return g;
}

ll invmod(ll a, ll mod) {
	ll x, y;
	extgcd(a, mod, x, y);
	x %= mod;
	if (x < 0) x += mod;
	return x;
}

// x % m[i] = r[i] % m[i] を満たす正で最小の x を返す
// mは互いに素であると仮定
// とりあえず解の存在判定は保留
ll garner(const vector<ll> &r, const vector<ll> &m) {
	ll n = r.size();
	ll m_prod = 1;
	ll x = r[0] % m[0];
	for (ll i = 1; i < n; i++) {
		m_prod *= m[i-1];
		ll t = ((r[i] - x) * invmod(m_prod, m[i])) % m[i];
		if (t < 0)t += m[i];
		x += t * m_prod;
	}
	return x;
}

constexpr u64 Modulus = MOD;
class Modint {
public:
	u64 num = 0;
	constexpr Modint() noexcept {}
	constexpr Modint(const u64 x) noexcept : num(x % Modulus) {}
	inline constexpr operator ll() const noexcept { return num; }
	inline constexpr Modint &operator+=(const Modint rhs) noexcept { num += rhs.num; if (num >= Modulus) num -= Modulus; return *this; }
	inline constexpr Modint operator+(const Modint rhs) const noexcept { return Modint(*this) += rhs; }
	inline constexpr Modint &operator-=(const Modint rhs) noexcept { if (num < rhs.num) num += Modulus; num -= rhs.num; return *this; }
	inline constexpr Modint operator-(const Modint rhs) const noexcept { return Modint(*this) -= rhs; }
	inline constexpr Modint &operator*=(const Modint rhs) noexcept { num = num * rhs.num % Modulus; return *this; }
	inline constexpr Modint operator*(const Modint rhs) const noexcept { return Modint(*this) *= rhs; }
	inline constexpr Modint &operator/=(const Modint rhs) noexcept { return operator*=(rhs.inv()); }
	constexpr Modint operator/(const Modint rhs) const noexcept { return Modint(*this) /= rhs; }
	inline constexpr Modint& operator++() noexcept { if (num == Modulus - 1) num = 0; else num++; return *this; }
	inline constexpr Modint operator++(int) noexcept { Modint ans(*this); operator++(); return ans; }
	inline constexpr Modint& operator--() noexcept { if (num == 0) num = Modulus - 1; else num--; return *this; }
	inline constexpr Modint operator--(int) noexcept { Modint ans(*this); operator--(); return ans; }
	inline constexpr Modint operator-() noexcept { return Modint(0) -= *this; }
	template<class T> inline constexpr Modint &operator+=(T x) noexcept { return operator+=(Modint(x)); }
	template<class T> inline constexpr Modint &operator+(T x) noexcept { return Modint(*this) += x; }
	template<class T> inline constexpr Modint &operator-=(T x) noexcept { return operator-=(Modint(x)); }
	template<class T> inline constexpr Modint &operator-(T x) noexcept { return Modint(*this) -= x; }
	template<class T> inline constexpr Modint &operator*=(T x) noexcept { return operator*=(Modint(x)); }
	template<class T> inline constexpr Modint &operator*(T x) noexcept { return Modint(*this) *= x; }
	template<class T> inline constexpr Modint &operator/=(T x) noexcept { return operator/=(Modint(x)); }
	template<class T> inline constexpr Modint &operator/(T x) noexcept { return Modint(*this) /= x; }
	inline constexpr Modint inv() const noexcept { ll x = 0, y = 0; extgcd(num, Modulus, x, y); return x; }
	static inline constexpr ll extgcd(ll a, ll b, ll &x, ll &y) noexcept { ll g = a; x = 1; y = 0; if(b){ g = extgcd(b, a % b, y, x); y -= a / b * x; } return g; }
	inline constexpr Modint pow(ull x) const noexcept { Modint ans = 1, cnt = *this; while(x){ if(x & 1) ans *= cnt; cnt *= cnt; x /= 2; } return ans; }
	template<class T> constexpr Modint(T x) noexcept {
		using U = typename conditional<sizeof(T) >= 4, T, int>::type;
		U y = x; y %= U(Modulus); if(y < 0) y += Modulus; num = uint(y);
	}
};
std::istream& operator>>(std::istream& is, Modint& x){ ll a; cin >> a; x = a; return is; }
// inline constexpr Modint operator""_M(ull x) noexcept { return Modint(x); }
std::vector<Modint> fac(1, 1), inv(1, 1);
inline void reserve(ll a){
	if(fac.size() >= a) return;
	if(a < fac.size() * 2) a = fac.size() * 2;
	if(a >= Modulus) a = Modulus;
	while(fac.size() < a) fac.push_back(fac.back() * Modint(fac.size()));
	inv.resize(fac.size());
	inv.back() = fac.back().inv();
	for(ll i = inv.size() - 1; !inv[i - 1]; i--) inv[i - 1] = inv[i] * i;
}
inline Modint fact(ll n){ if(n < 0) return 0; reserve(n + 1); return fac[n]; }
inline Modint perm(ll n, ll r){
	if(r < 0 || n < r) return 0;
	if(n >> 24){ Modint ans = 1; for(ll i = 0; i < r; i++) ans *= n--; return ans; }
	reserve(n + 1); return fac[n] * inv[n - r];
}
// 階乗やその逆元をメモ化すると速い
// modを取りたくないならnCk/2^Nをパスカルの三角形で作る
inline Modint comb(ll n, ll r){ if(r < 0 || n < r) return 0; reserve(r + 1); return perm(n, r) * inv[r]; }
inline Modint Mcomb(ll n, ll r){ return comb(n + r - 1, n - 1); } // r balls into n boxes
inline Modint catalan(ll n){ reserve(n * 2 + 1); return fac[n * 2] * inv[n] * inv[n + 1]; }


/*
class runtime_modint {
	using u64 = std::uint_fast64_t;

	static u64 &mod() {
		static u64 mod_ = 0;
		return mod_;
	}

public:
	u64 a;

	runtime_modint(const u64 x = 0) : a(x % get_mod()) {}
	u64 &value() noexcept { return a; }
	const u64 &value() const noexcept { return a; }
	runtime_modint operator+(const runtime_modint rhs) const {
		return runtime_modint(*this) += rhs;
	}
	runtime_modint operator-(const runtime_modint rhs) const {
		return runtime_modint(*this) -= rhs;
	}
	runtime_modint operator*(const runtime_modint rhs) const {
		return runtime_modint(*this) *= rhs;
	}
	runtime_modint operator/(const runtime_modint rhs) const {
		return runtime_modint(*this) /= rhs;
	}
	runtime_modint &operator+=(const runtime_modint rhs) {
		a += rhs.a;
		if (a >= get_mod()) {
			a -= get_mod();
		}
		return *this;
	}
	runtime_modint &operator-=(const runtime_modint rhs) {
		if (a < rhs.a) {
			a += get_mod();
		}
		a -= rhs.a;
		return *this;
	}
	runtime_modint &operator*=(const runtime_modint rhs) {
		a = a * rhs.a % get_mod();
		return *this;
	}
	runtime_modint &operator/=(runtime_modint rhs) {
		u64 exp = get_mod() - 2;
		while (exp) {
			if (exp % 2) {
				*this *= rhs;
			}
			rhs *= rhs;
			exp /= 2;
		}
		return *this;
	}

	static void set_mod(const u64 x) { mod() = x; }
	static u64 get_mod() { return mod(); }
};*/

constexpr ll mx = 4;
class Matrix {
public:
	using T = Modint;
	T m[mx][mx];
	// コンストラクタ
	constexpr Matrix() noexcept {}
	// アクセス
	const T* operator[](const ll i) const { return m[i]; } // read
	T* operator[](const ll i) { return m[i]; } // write
	// 演算
	inline constexpr Matrix &operator+=(const Matrix &x) noexcept { for(ll i = 0; i < mx; i++) for(ll j = 0; j < mx; j++) m[i][j] += x[i][j]; return *this; }
	inline constexpr Matrix operator+(const Matrix x) const noexcept { return Matrix(*this) += x; }
	inline constexpr Matrix &operator-=(const Matrix &x) noexcept { for(ll i = 0; i < mx; i++) for(ll j = 0; j < mx; j++) m[i][j] -= x[i][j]; return *this; }
	inline constexpr Matrix operator-(const Matrix &x) noexcept { return Matrix(*this) -= x; }
	// O(N^3)
	inline constexpr Matrix &operator*=(Matrix &x) noexcept { *this = *this * x; return *this; }
	inline constexpr Matrix operator*(Matrix &x) { Matrix c; for(ll i = 0; i < mx; i++) for(ll j = 0; j < mx; j++) for(ll k = 0; k < mx; k++) { T a = m[i][j] * x[j][k]; c[i][k] += a; } return c; }
	// E^M O(N^3logM)
	inline constexpr Matrix pow(ll b) const noexcept { Matrix a = *this, c = E(); while (b) { if(b & 1) c *= a; if(b >>= 1) a *= a; } return c; }
	inline constexpr Matrix static E() noexcept { Matrix a; for(ll i = 0; i < mx; i++) a[i][i] = 1; return a; }
	inline constexpr bool operator==(const Matrix &a) { bool flg = true; for(ll i = 0; i < mx; i++) for(ll j = 0; j < mx; j++) if(m[i][j] != a[i][j]) flg = false; return flg; }
	// 行列とスカラの演算
	inline constexpr Matrix &operator+=(const T &a) { for(ll i = 0; i < mx; i++) for(ll j = 0; j < mx; j++) m[i][j] += a; return *this; }
	inline constexpr Matrix &operator-=(const T &a) { for(ll i = 0; i < mx; i++) for(ll j = 0; j < mx; j++) m[i][j] -= a; return *this; }
	inline constexpr Matrix &operator*=(const T &a) { for(ll i = 0; i < mx; i++) for(ll j = 0; j < mx; j++) m[i][j] *= a; return *this; }
	inline constexpr Matrix &operator/=(const T &a) { for(ll i = 0; i < mx; i++) for(ll j = 0; j < mx; j++) m[i][j] /= a; return *this; }
	inline constexpr Matrix operator+(const T &a) const { return Matrix(*this) += a; }
	inline constexpr Matrix operator-(const T &a) const { return Matrix(*this) -= a; }
	inline constexpr Matrix operator*(const T &a) const { return Matrix(*this) *= a; }
	inline constexpr Matrix operator/(const T &a) const { return Matrix(*this) /= a; }
	// 転置行列
	inline constexpr Matrix t() { Matrix m2; for(ll i = 0; i < mx; i++) for(ll j = 0; j < mx; j++) m2[i][j] = m[j][i]; return m2; }

	inline constexpr void show() {
		for(ll i = 0; i < mx; i++) {
			for(ll j = 0; j < mx; j++) {
				if(j != 0) cout << " ";
				cout << m[i][j];
			}
			cout << endl;
		}
		return ;
	}
};

struct SlopeTrick
{
	ll minf = -1;
	priority_queue<ll> L;
	pq<ll> R;

	ll shift_left = -1;
	ll shift_right = -1;

	SlopeTrick() {}

private:
	void L_push(ll a) { L.push(a + shift_left); }
	ll L_top()
	{
		if (L.empty())
			return -LINF;
		else
			return L.top() - shift_left;
	}
	ll L_pop()
	{
		ll l-1 = L_top();
		L.pop();
		return l-1;
	}
	void R_push(ll a) { R.push(a + shift_right); }
	ll R_top()
	{
		if (R.empty())
			return LINF;
		else
			return R.top() - shift_right;
	}
	ll R_pop()
	{
		ll r-1 = R_top();
		R.pop();
		return r-1;
	}

public:
	ll min() { return minf; }
	void add(ll a) { minf += a; }
	void slope_right(ll a)
	{
		if (!L.empty() && a < L_top())
		{
			minf += L_top() - a;
			L_push(a);
			R_push(L_pop());
		}
		else
			R_push(a);
	}
	void slope_left(ll a)
	{
		if (!R.empty() && a > R_top())
		{
			minf += a - R_top();
			R_push(a);
			L_push(R_pop());
		}
		else
			L_push(a);
	}
	void slope_abs(ll a)
	{
		slope_right(a);
		slope_left(a);
	}
	void min_right()
	{
		while (!R.empty())
			R.pop();
	}
	void min_left()
	{
		while (!L.empty())
			L.pop();
	}
	void shift(ll a, ll b)
	{
		shift_left += a;
		shift_right += b;
	}
	ll access(ll a)
	{
		ll y = minf;
		while (!L.empty())
			y += max(-1LL, L_pop() - a);
		while (!R.empty())
			y += max(-1LL, a - R_pop());
		return y;
	}

	void Debug()
	{
		cout << "L ";
		while (!L.empty())
		{
			cout << L_pop() << " ";
		}
		cout << endl;
		cout << "R ";
		while (!R.empty())
		{
			cout << R_pop() << " ";
		}
		cout << endl;
		cout << minf << endl;
	}
};