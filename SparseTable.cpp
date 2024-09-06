#include "bits/stdc++.h"
using namespace std;
#define int long long

struct SparseTable {

    const int LOG = 25;
    vector<vector<int>> val;
    int n;

    SparseTable(vector<int> &arr) {
        n = arr.size();
        val = vector<vector<int>> (n, vector<int> (LOG));

        // val[i][j] will store the combined information of the subarray
        // starting from i and length 2^j

        for (int i = 0; i < n; i++)
            val[i][0] = arr[i];

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                int nextInd = i + (1 << (j - 1));
                if (nextInd >= n) break;
                val[i][j] = merge(val[i][j - 1], val[nextInd][j - 1]);
            }
        }
    }

    int merge(int a, int b) {
        // idempotent operations
        // with two values, do the required operations
        // e.g. gcd, min, max
        return min(a, b);
    }

    int getAnswer(int i, int j) {
        // for subarray i to j, what is the answer
        int length = j - i + 1;
        int bin_log_length = log2(length);

        // both subarray length should be bin_log_length
        // one will start from index i
        // another will end at index j

        int left_part_answer = val[i][bin_log_length];
        int right_part_answer = val[j + 1 - (1 << bin_log_length)][bin_log_length];

        return merge(left_part_answer, right_part_answer);
    }
};

void test_case() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    SparseTable s(a);

    while (q--) {
        int i, j;
        cin >> i >> j;
        i--;
        j--;
        cout << s.getAnswer(i, j) << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    test_case();
    return 0;
}

// Problem Link: https://cses.fi/problemset/task/1647/