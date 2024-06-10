
struct DSU {
	int connected;
	vector<int> par, sz;

	DSU(int n) {
		connected = n;
		par = sz = vector<int> (n + 1);
		for (int i = 0; i <= n; i++) {
			par[i] = i;
			sz[i] = 1;
		}
	}

	int find_parent(int v) {
		if (v == par[v])
			return v;
		return par[v] = find_parent(par[v]);
	}

	bool same_set(int a, int b) {
		return find_parent(a) == find_parent(b);
	}

	int getSize(int v) {
		return sz[find_parent(v)];
	}

	void merge(int a, int b) {
		a = find_parent(a);
		b = find_parent(b);
		if (a == b) return;
		connected--;
		if (sz[a] < sz[b])
			swap(a, b);
		par[b] = a;
		sz[a] += sz[b];
	}
};