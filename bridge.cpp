
// finding bridges in the graph
vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int u, int par = -1) {
	visited[v] = true;
	tin[u] = low[u] = timer++;

	for (int v : adj[u]) {
		if (v == par)
			continue;
		if (visited[v]) {
			// back edge
			low[u] = min(low[u], tin[v]);
		} else {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > tin[u]) {
				// found a bridge
				cout << u << " " << v << "\n";
			}
		}
	}
}

void find_bridges() {
	visited = vector<bool> (n);
	tin = low = vector<int> (n);
	timer = 0;
	for (int i = 0; i < n; i++)
		if (!visited[i])
			dfs(i);
}