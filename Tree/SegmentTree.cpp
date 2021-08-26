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
	// 多数のU(U)にするf1の合成 つまりU^len
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