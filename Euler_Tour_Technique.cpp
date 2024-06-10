#include "bits/stdc++.h"
using namespace std;
#define int long long

struct Node {
    int sum;
};

struct SegmentTree {
    int len;
    vector<Node> values;

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Node single(int val) {
        // value at the base level while updating
        return {val};
    }

    Node neutral = {0}; // the value which will not affect our answer

    Node merge(Node a, Node b) {
        // the associative operation we are doing
        // a is left subsegment, b is right subsegment
        return {a.sum + b.sum};
    }
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    SegmentTree(int n) {
        len = 1;
        while (len < n) len *= 2;
        values = vector<Node> (2 * len);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        // leaf node
        if (rx - lx == 1) {
            // if lx is within the original array
            if (lx < (int)a.size())
                values[x] = single(a[lx]);
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void build(vector<int> &a) {
        build(a, 0, 0, len);
    }

    void update(int ind, int val, int x, int lx, int rx) {
        // x is current node, lx and rx are borders of curr node
        if (rx - lx == 1) { // leaf node
            // bottom level of the segtree
            values[x] = single(val);
            return;
        }

        int mid = (lx + rx) / 2;

        if (ind < mid) {
            // go to left subtree
            update(ind, val, 2 * x + 1, lx, mid);
        } else {
            // go to right subtree
            update(ind, val, 2 * x + 2, mid, rx);
        }
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void update(int ind, int val) {
        update(ind, val, 0, 0, len);
    }

    Node calc(int l, int r, int x, int lx, int rx) {
        // current range do not intersect with required range
        if (r <= lx or l >= rx)
            return neutral;
        // whole segment lie in this range
        if (l <= lx and r >= rx)
            return values[x];

        int mid = (lx + rx) / 2;

        Node leftVal = calc(l, r, 2 * x + 1, lx, mid);
        Node rightVal = calc(l, r, 2 * x + 2, mid, rx);

        return merge(leftVal, rightVal);
    }

    Node calc(int l, int r) {
        return calc(l, r, 0, 0, len);
    }
};

const int N = 2e5 + 5;
vector<int> tree[N];
vector<int> time_in(N), time_out(N);
vector<int> val(N);
vector<int> a;
int n, q, timer;

void dfs(int u, int par) {
    time_in[u] = timer;
    a[timer] = val[u];
    timer++;
    for (int v : tree[u]) {
        if (v == par)
            continue;
        dfs(v, u);
    }
    time_out[u] = timer - 1;
}

void test_case() {
    cin >> n >> q;
    a = vector<int> (n);
    for (int i = 0; i < n; i++)
        cin >> val[i];

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(0, 0);

    // time in for each node is the equivalent index in the segment tree
    // after flattening the tree

    SegmentTree st(n);
    st.build(a);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int node, val;
            cin >> node >> val;
            node--;
            st.update(time_in[node], val);
        } else {
            int node;
            cin >> node;
            node--;
            int len = time_out[node] - time_in[node] + 1;
            int ind = time_in[node];
            int ans = st.calc(ind, ind + len).sum;
            cout << ans << "\n";
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    test_case();
    return 0;
}
