#include "bits/stdc++.h"
using namespace std;
#define int long long
 
const int N = 2e5 + 5;
vector<int> adj[N];
int n, q;
 
const int LOG = 21;
vector<vector<int>> up(N, vector<int> (LOG));
vector<int> depth(N);
 
void dfs(int v, int p) {
	up[v][0] = p;
	for (int i = 1; i < LOG; i++)
		up[v][i] = up[up[v][i - 1]][i - 1];
 
	for (int &u : adj[v]) {
		if (u != p) {
			depth[u] = 1 + depth[v];
			dfs(u, v);
		}
	}
}
 
// binary lifting
int jump(int u, int k) {
	for (int i = LOG - 1; i >= 0; i--)
		if (k & (1 << i))
			u = up[u][i];
	return u;
}
 
int lca(int a, int b) {
	if (depth[a] < depth[b])
		swap(a, b);
 
	a = jump(a, depth[a] - depth[b]);
	if (a == b) return a;
	// get both to the same level and move up parallely
 
	for (int i = LOG - 1; i >= 0; i--) {
		if (up[a][i] != up[b][i]) {
			a = up[a][i];
			b = up[b][i];
		}
	}
 
	return up[a][0];
}
 
void test_case() {
	cin >> n >> q;
	for (int i = 1; i < n; i++) {
		int v;
		cin >> v;
		--v;
		adj[i].push_back(v);
		adj[v].push_back(i);
	}
 
	dfs(0, 0);
 
	while (q--) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		cout << lca(u, v) + 1 << "\n";
	}
}
 
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	test_case();
	return 0;
}

// Problem Link: https://cses.fi/problemset/task/1688