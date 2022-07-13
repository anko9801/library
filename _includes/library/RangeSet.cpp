class RangeSet : public set<pair<long long, long long>> {
private:
	bool flagToMergeAdjacentSegment;

public:
	RangeSet(bool flagToMergeAdjacentSegment) : flagToMergeAdjacentSegment(flagToMergeAdjacentSegment) {}

	// get the iterator that x is in
	// noexist -> map.end()
	auto get(ll x) const {
		auto itr = upper_bound(pll(x, 1e18));
		if (itr == begin() or (--itr)->second < x) return end();
		return itr;
	}

	// insert segment [l, r)
	// return merged range
	auto add(pll lr) {
		while (true) {
			auto itr = lower_bound(pll(lr.first, -INF));
			if (itr == end()) break;
			ll r = -INF;
			if (itr->first <= lr.second + (int)flagToMergeAdjacentSegment) r = max(lr.second, itr->second);
			if (r == -INF) break;
			lr.second = r;
			erase(itr);
		}

		while (true) {
			auto itr = lower_bound(pll(lr.first, -INF));
			if (itr == begin()) break;
			itr--;
			ll l = INF;
			ll r = -INF;
			if (itr->second + (int)flagToMergeAdjacentSegment >= lr.first) {
				l = min(lr.first, itr->first);
				r = max(lr.second, itr->second);
			}
			if (l == INF) break;
			lr.first = l;
			lr.second = r;
			erase(itr);
		}
		insert(lr);
		return lower_bound(lr);
	}

	// Are x1 and x2 in the same range?
	bool same(ll x1, ll x2) {
		auto itr = get(x1);
		return itr != end() and (itr->first <= x2 and x2 <= itr->second);
	}
};
