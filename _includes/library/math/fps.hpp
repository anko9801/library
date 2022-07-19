using mint = Modint;
using vm = vector<mint>;

struct fps : vm {
#define d (*this)
#define s int(vm::size())
	template<class...Args> fps(Args...args): vm(args...) {}
	fps(initializer_list<mint> a): vm(a.begin(),a.end()) {}
	void rsz(int n) { if (s < n) vm.resize(n);}
	mint& operator[](int i) { rsz(i+1); return vm::operator[](i);}
	mint operator[](int i) const { return i<s ? vm::operator[](i) : 0;}
	fps operator-() const { fps r(d); rep(i,s) r[i] = -r[i]; return r;}
	fps& operator+=(const fps& a) { rsz(a.size()); rep(i,a.size()) d[i] += a[i]; return d;}
	fps& operator-=(const fps& a) { rsz(a.size()); rep(i,a.size()) d[i] -= a[i]; return d;}
	fps& operator*=(const fps& a) { return d = convolution(d, a);}
	fps operator+(const fps& a) const { return fps(d) += a;}
	fps operator-(const fps& a) const { return fps(d) -= a;}
	fps operator*(const fps& a) const { return fps(d) *= a;}
#undef s
#undef d
};
