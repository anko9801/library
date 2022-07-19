class RangeSet : public set<pll> {
private:
	bool flagToMergeAdjacentSegment = true;

public:
	RangeSet() : flagToMergeAdjacentSegment(true) {}
	RangeSet(bool flagToMergeAdjacentSegment) : flagToMergeAdjacentSegment(flagToMergeAdjacentSegment) {}

	// get the iterator that x is in range
	// no exist -> map.end()
	auto get(ll x) const {
		auto itr = upper_bound({x, 1e18});
		// l <= r < x < l' <= r'
		if (itr == begin() or (--itr)->second < x) return end();
		return itr;
	}

	// insert segment [l, r]
	// return merged range
	auto add(pll lr) {
		// l <= l'
		// [l, r] ∪ [l', r'] => [l, r']
		while (true) {
			auto itr = lower_bound({lr.first, -INF});
			if (itr == end()) break;
			ll r = -INF;
			// piled => [l, r']
			if (itr->first <= lr.second + (int)flagToMergeAdjacentSegment) r = max(lr.second, itr->second);
			if (r == -INF) break;
			lr.second = r;
			erase(itr);
		}

		// l' < l
		// [l', r'] ∪ [l, r] => [l', r']
		while (true) {
			auto itr = lower_bound({lr.first, -INF});
			if (itr == begin()) break;
			itr--;
			ll l = INF;
			ll r = -INF;
			// piled => [l', r']
			if (lr.first <= itr->second + (int)flagToMergeAdjacentSegment ) {
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

// TODO
// kd-tree