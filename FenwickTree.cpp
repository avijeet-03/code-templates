
struct FenwickTree {
	// 1 based indexing tree
	int n;
	vector<int> tree;

	FenwickTree (int len) {
		n = len;
		tree = vector<int> (n + 1);
	}

	int lsb(int pos) {
		return pos & (-pos);
	}

	void build(vector<int> &a) {
		// a is 0 indexed
		for (int i = 1; i <= n; i++) {
			tree[i] += a[i - 1];
			int nxt_ind = i + lsb(i);
			if (nxt_ind <= n)
				tree[nxt_ind] += tree[i];
		}
	}

	void update(int ind, int val) {
		// val is the delta we need to increment
		// we have to reset the original array before every update
		// if we want to update directly
		while (ind <= n) {
			tree[ind] += val;
			ind += lsb(ind);
		}
	}

	int pref_calc(int ind) {
		int ans = 0;
		while (ind > 0) {
			ans += tree[ind];
			ind -= lsb(ind);
		}
		return ans;
	}

	int range_query(int l, int r) {
		// [l.......r]
		return pref_calc(r) - pref_calc(l - 1);
	}
};