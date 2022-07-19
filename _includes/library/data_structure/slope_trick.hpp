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
