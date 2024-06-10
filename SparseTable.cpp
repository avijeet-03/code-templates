
struct SparseTable {
	const int LOG = 25;
	vector<int> bin_log;
	vector<vector<int>> val;
	int n;

	SparseTable (int len) {
		n = len;
		bin_log = vector<int> (n + 1);
		val = vector<vector<int>> (n + 1, vector<int> (LOG));
		// val[i][j] :- result of the range [i.....i + 2^j - 1]
	}

	int merge(int a, int b) {
		// idempotent operation
		// operation can be applied multiple times
		// without changing the result
		return min(a, b);
	}

	void build(vector<int> &a) {
		bin_log[1] = 0;
		for (int i = 2; i <= n; i++)
			bin_log[i] = bin_log[i / 2] + 1;

		for (int i = 0; i < n; i++)
			val[i][0] = a[i];

		for (int j = 1; j < LOG; j++) {
			for (int i = 0; i + (1 << j) - 1 < n; i++) {
				val[i][j] = merge(val[i][j - 1], val[i + (1 << (j - 1))][j - 1]);
			}
		}
		// O(n * logn)
	}

	int query(int l, int r) {
		int length = r - l + 1;
		int k = bin_log[length];
		return merge(val[l][k], val[r - (1 << k) + 1][k]);
	}
};

// Problem Link: https://cses.fi/problemset/task/1647/
// Submission Link: https://cses.fi/paste/a532be5ca0fdb542382baa/