#include "bits/stdc++.h"
using namespace std;
#define int long long

vector<int> a;
vector<int> dp;
vector<vector<int>> tree;
int n;

void dfs(int u, int par) {
    for (int v : tree[u]) {
        if (v == par)
            continue;
        dfs(v, u);
        a[u] += max(0LL, a[v]);
    }
}

void rerooting(int u, int par) {
    for (int v : tree[u]) {
        if (v == par)
            continue;
        a[v] += max(0LL, a[u] - max(0LL, a[v]));
        rerooting(v, u);
    }
}

void test_case() {
    cin >> n;
    a = dp = vector<int> (n);
    tree = vector<vector<int>> (n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 0)
            a[i]--;
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(0, 0);
    rerooting(0, 0);

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    test_case();
    return 0;
}

/*
    - first cut one branch of the root and notice the changes
    - take the rest of the tree and shift it to as one of the subtree of the new root
    - and calculate the answer
*/

// https://codeforces.com/contest/1324/problem/F