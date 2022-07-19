/**
 * @brief Binary Indexed Tree(Fenwick Tree)
 * @note sum O(logN) update O(logN) maxも2次元もできる
 */
template<typename T>
struct BinaryIndexedTree {
	int N;
	vector<T> data;

	BinaryIndexedTree(int size) {
		// 0-indexed 1-indexed
		N = size + 2;
		data.assign(N + 1, {});
	}

	// get sum of [0, k]
	T sum(int k) const {
		if (k < 0) return T{};
		T ret{};
		for(++k; k > 0; k -= k & -k) ret += data[k];
		return ret;
	}

	// get sum of [l, r]
	inline T sum(int l, int r) const { return sum(r) - sum(l - 1); }

	// get value of k
	inline T operator[](int k) const { return sum(k) - sum(k - 1); }

	// data[k] += x
	void add(int k, T x) {
		for(++k; k < N; k += k & -k) data[k] += x;
	}

	// range add x to [l, r]
	void imos(int l, int r, T x) {
		add(l, x);
		add(r + 1, -x);
	}

	// minimize i s.t. sum(i) >= w
	int lower_bound(T w) {
		if (w <= 0) return 0;
		int x = 0;
		for (int k = 1 << __lg(N); k > 0; k >>= 1) {
			if (x + k < N && data[x + k] < w) {
				w -= data[x + k];
				x += k;
			}
		}
		return x;
	}

	// minimize i s.t. sum(i) > w
	int upper_bound(T w) {
		if (w < 0) return 0;
		int x = 0;
		for (int k = 1 << __lg(N); k > 0; k >>= 1) {
			if (x + k <= N && data[x + k] <= w) {
				w -= data[x + k];
				x += k;
			}
		}
		return x;
	}
};

// 転倒数 重複あり
template<typename T>
ll inversion_counting(const vector<T> &v) {
	vector<T> xs{v};
	sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.ned());
	int N = xs.size();
	BinaryIndexedTree<T> bin(N);
	ll ans = 0;
	for (ll i = 0; i < N; i++) {
		int s = lower_bound(xs.begin(), xs.end(), xs[i]) - xs.begin();
		ans += i - bin.sum(v[i]);
		bin.add(v[i], 1);
	}
	return ans;
}

// 隣接 swap によって v を w に変えるのにかかる手数 (不可能 : -1)
template<typename T>
ll swap_distance(const vector<T> &v, const vector<T> &w) {
	if (v.size() != w.size()) return -1;

	ll N = v.size();
	vector<pair<T, int>> vv(N), ww(N);
	for (int i = 0; i < N; i++) {
		vv[i] = make_pair(v[i], i);
		ww[i] = make_pair(w[i], i);
	}
	sort(vv.begin(), vv.end());
	sort(ww.begin(), ww.end());
	vector<int> order(N);
	for (int i = 0; i < N; i++) {
		if (vv[i].first != ww[i].first) return -1;
		order[vv[i].second] = ww[i].second;
	}
	return inversion_counting(order);
}
