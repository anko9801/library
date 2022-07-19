template<class T, class U>
class LazySegmentTree {
	void eval(int k, int len) {
		if (lazy[k] == e1) return;
		// len個分のlazy[k]を評価
		node[k] = g(node[k], segpow(lazy[k], len));
		if (k < N - 1) {
			// 最下段でなければ下のlazyに伝搬
			lazy[2*k+1] = f1(lazy[2*k+1], lazy[k]);
			lazy[2*k+2] = f1(lazy[2*k+1], lazy[k]);
		}
		lazy[k] = e1;
	}

	// k番目のノード[l, r)について、[a, b)の範囲にxを作用
	void update(int a, int b, U x, int k, int l, int r) {
		eval(k, r - l);
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) {
			lazy[k] = f1(lazy[k], x);
			eval(k, r - l);
			return;
		}
		update(a, b, x, 2*k+1, l, (l + r) / 2);
		update(a, b, x, 2*k+2, (l + r) / 2, r);
		node[k] = f0(node[2 * k + 1], node[2 * k + 2]);
	}

	// k番目のノード[l, r)について、[a, b)のクエリを求める
	T query(int a, int b, int k, int l, int r) {
		eval(k, r - l);
		if (b <= l || r <= a) return e0;
		if (a <= l && r <= b) return node[k];
		T vl = query(a, b, 2*k+1, l, (l + r) / 2);
		T vr = query(a, b, 2*k+2, (l + r) / 2, r);
		return f0(vl, vr);
	}

public:
	int sz, N;
	vector<T> node;
	vector<U> lazy;
	// node T上の演算、単位元
	using F0 = function<T(T, T)>;
	F0 f0;
	T e0;
	// lazy U上の演算、単位元
	using F1 = function<U(U, U)>;
	F1 f1;
	U e1;
	// 作用
	using G = function<T(T, U)>;
	G g;
	// 多数のU(U)にするf1の合成 つまりU^n
	using P = function<U(U, int)>;
	P segpow;

	LazySegmentTree(const vector<T> &a, F0 f0, T e0, F1 f1, U e1, G g, P segpow)
			: sz(a.size()), f0(f0), e0(e0), f1(f1), e1(e1), g(g), segpow(segpow) {
		for (N = 1; N < sz; N *= 2);
		node.resize(2*N-1);
		lazy.resize(2*N-1, e1);
		for (int i = 0; i < sz; i++) node[N-1+i] = a[i];
		for (int i = N - 2; i >= 0; i--) node[i] = f0(node[2*i+1], node[2*i+2]);
	}

	// [a, b)にxを作用
	void update(int a, int b, U x) { update(a, b, x, 0, 0, N); }
	void update(int a, U x) { update(a, a+1, x); }
	// [a, b)
	T query(int a, int b) { return query(a, b, 0, 0, N); }
	T query(int a) { return query(a, a+1); }
};

// Min & Update
LazySegmentTree<ll, ll> seg(
	vector<ll>(n, (1LL << 31) - 1),
	[](ll x, ll y) { return min(x, y); }, 1e18,
	[](ll x, ll y) { return y == 1e18 ? x : y; }, 1e18,
	[](ll x, ll y) { return y == 1e18 ? x : y; },
	[](ll y, ll len) { return y; }
);

// Sum & Add
LazySegmentTree<ll, ll> seg(
	vector<ll>(n, 0),
	plus<>(), 0,
	plus<>(), 0,
	plus<>(),
	multiplies<>(),
);

// Min & Add
LazySegmentTree<ll, ll> seg(
	vector<ll>(n, 0),
	[](ll x, ll y) { return min(x, y); }, 1e18,
	plus<>(), 0,
	plus<>(),
	[](ll y, ll len) { return y; }
);

// Sum & Update
LazySegmentTree<ll, ll> seg(
	vector<ll>(n),
	plus<>(), 0,
	[](ll x, ll y) { return y == 1e18 ? x : y; }, 1e18,
	[](ll x, ll y) { return y == 1e18 ? x : y; },
	[](ll y, ll len) { return y == 1e18 ? 1e18 : y * len; }
);

// Sum & Affine
LazySegmentTree<pll, pll> seg(
	vector<pll>(n),
	[](pll x, pll y) { return {x.fi + y.fi, x.se + y.se}; }, {0, 0},
	[](pll x, pll y) { return {x.fi * y.fi, x.se * y.fi + y.se}; }, {1, 0},
	[](pll x, pll y) { return {x.fi * y.fi, x.se * y.fi + y.se}; },
	[](pll y, ll len) { return {y.fi, y.se * len}; },
);

// Range Or & range update
LazySegmentTree<ll, ll> seg(
	vector<ll>(n),
	[](ll x, ll y) { return x | y; }, 0,
	[](ll x, ll y) { return y == 1e18 ? x : y; }, 1e18,
	[](ll x, ll y) { return y == 1e18 ? x : y; },
	[](ll y, ll len) { return y; }
);

// TODO
class SegmentTreeBeats {
};

// クエリ O(logN)
template<typename T>
struct BinaryIndexedTree {
	vector<T> data;

	BinaryIndexedTree(int sz) {
		data.assign(++sz, 0);
	}

	T sum(int k) {
		T ret = 0;
		for(++k; k > 0; k -= k & -k) ret += data[k];
		return (ret);
	}

	void add(int k, T x) {
		for(++k; k < data.size(); k += k & -k) data[k] += x;
	}
};

template<typename T>
struct SparseTable {
	vector<vector<T>> st;
	vector<int> lookup;

	SparseTable(const vector<T> &v) {
		int b = 0;
		while((1 << b) <= v.size()) ++b;
		st.assign(b, vector<T>(1 << b));
		for (int i = 0; i < v.size(); i++) {
			st[0][i] = v[i];
		}
		for (int i = 1; i < b; i++) {
			for (int j = 0; j + (1 << i) <= (1 << b); j++) {
				st[i][j] = min(st[i-1][j], st[i-1][j + (1 << (i - 1))]);
			}
		}
		lookup.resize(v.size() + 1);
		for (i = 2; i < lookup.size(); i++) {
			lookup[i] = lookup[i >> 1] + 1;
		}
	}
};

// 構築 O(NlogN)
// クエリ O(1)
template< typename T >
struct SparseTable {
	vector< vector< T > > st;
	vector< int > lookup;

	SparseTable(const vector< T > &v) {
		int b = 0;
		while((1 << b) <= v.size()) ++b;
		st.assign(b, vector< T >(1 << b));
		for(int i = 0; i < v.size(); i++) {
			st[0][i] = v[i];
		}
		for(int i = 1; i < b; i++) {
			for(int j = 0; j + (1 << i) <= (1 << b); j++) {
				st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
			}
		}
		lookup.resize(v.size() + 1);
		for(int i = 2; i < lookup.size(); i++) {
			lookup[i] = lookup[i >> 1] + 1;
		}
	}

	inline T rmq(int l, int r) {
		int b = lookup[r - l];
		return min(st[b][l], st[b][r - (1 << b)]);
	}
};
