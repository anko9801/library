
class Eratosthenes {
public:
	vector<bool> isprime; // 素数
	vector<ll> minfactor; // 最小の素因数
	// メビウス関数 μ
	// μ(1)=1
	// n がある素数pで2回以上割り切れるとき、μ(n)=0
	// n=p1×p2×…pK と素因数分解できるとき、μ(n)=(−1)^K
	// f(1)=∑[i=1~N]μ(i)F(i) 約数系包除原理
	vector<ll> mobius;

	// エラトステネスの篩 O(NloglogN)
	Eratosthenes(int N) : isprime(N+1, true), minfactor(N+1, -1), mobius(N+1, 1) {
		isprime[1] = false;
		minfactor[1] = 1;

		for (ll p = 2; p <= N; ++p) {
			if (!isprime[p]) continue;
			minfactor[p] = p;
			mobius[p] = -1;
			for (ll q = p * 2; q <= N; q += p) {
				isprime[q] = false;
				if (minfactor[q] == -1) minfactor[q] = p;
				if ((q / p) % p == 0) mobius[q] = 0;
				else mobius[q] = -mobius[q / p];
			}
		}
	}

	// 高速素因数分解 O(NlogN)
	vector<pll> factorize(int n) {
		vector<pll> res;
		while (n > 1) {
			ll p = minfactor[n];
			ll exp = 0;

			while (minfactor[n] == p) {
				n /= p;
				++exp;
			}
			res.emplace_back(p, exp);
		}
		return res;
	}

	// 高速約数列挙 O(\sigma n)
	vector<ll> divisors(ll n) {
		vector<ll> res({1});
		vector<pll> pf = factorize(n);

		for (auto [p, e] : pf) {
			ll s = (ll)res.size();
			for (ll i = 0; i < s; ++i) {
				ll v = res[i];
				for (ll j = 0; j < e; ++j) {
					v *= p;
					res.push_back(v);
				}
			}
		}
		return res;
	}

	// 高速ゼータ変換 O(NloglogN)
	// F(n)=∑[n|i]f(i)
	template<class T> void fast_zeta(vector<T> &f) {
		ll N = f.size();
		for (ll p = 2; p < N; ++p) {
			if (!isprime[p]) continue;
			for (ll k = (N-1) / p; k >= 1; --k) {
				f[k] += f[k * p];
			}
		}
	}

	// 高速メビウス変換 O(NloglogN)
	// f(n)=∑[n|i]μ(i/n)F(i)
	template<class T> void fast_mobius(vector<T> &F) {
		ll N = F.size();
		for (ll p = 2; p < N; ++p) {
			if (!isprime[p]) continue;
			for (ll k = 1; k * p < N; ++k) {
				F[k] -= F[k * p];
			}
		}
	}

	// 添字GCD畳み込み O(NloglogN)
	// h(n)=∑[GCD(i,j)=n]f(i)g(j)
	// H(n)=F(n)G(n)
	template<class T> vector<T> gcd_conv(const vector<T> &f, const vector<T> &g) {
		ll N = max(f.size(), g.size());
		vector<T> F(N, 0), G(N, 0), H(N);
		for (ll i = 0; i < f.size(); ++i) F[i] = f[i];
		for (ll i = 0; i < g.size(); ++i) G[i] = g[i];

		fast_zeta(F);
		fast_zeta(G);

		for (ll i = 1; i < N; ++i) H[i] = F[i] * G[i];

		fast_mobius(H);

		return H;
	}
};