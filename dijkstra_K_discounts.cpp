#include "bits/stdc++.h"
using namespace std;
#define int long long
const int inf = 1e15;

const int N = 1e5 + 5;
vector<vector<int>> adj[N];
int n, m, k;

void test_case() {
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	vector<vector<int>> dp(n + 1, vector<int> (k + 1, inf));
	for (int j = 0; j <= k; j++)
		dp[1][j] = 0;

	set<pair<int, pair<int, int>>> s;
	s.insert({0, {1, 0}});

	while (!s.empty()) {
		auto [u, used] = s.begin()->second;
		s.erase(s.begin());

		// cerr << u << " " << used << "\n";

		for (auto &e : adj[u]) {
			int v = e[0], len = e[1];
			if (dp[u][used] + len < dp[v][used]) {
				s.erase({dp[v][used], {v, used}});
				dp[v][used] = dp[u][used] + len;
				s.insert({dp[v][used], {v, used}});
			}

			if (used == k) continue;

			if (dp[u][used] < dp[v][used + 1]) {
				s.erase({dp[v][used + 1], {v, used + 1}});
				dp[v][used + 1] = dp[u][used];
				s.insert({dp[v][used + 1], {v, used + 1}});
			}
		}
	}

	for (int i = 1; i <= n; i++)
		cout << *min_element(dp[i].begin(), dp[i].end()) << " ";
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	test_case();
	return 0;
}
