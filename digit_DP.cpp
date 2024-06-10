// Problem Link: https://cses.fi/problemset/task/2220/

#include "bits/stdc++.h"
using namespace std;
#define int long long

int dp[20][2][2][11];

int calc(string &num, int pos, int tight, int leading, int last) {
    if (pos >= (int)num.size()) return 1;

    int &res = dp[pos][tight][leading][last];
    if (res != -1) return res;

    int ub = (tight ? num[pos] - '0' : 9);

    int ans = 0;
    if (leading == 1) {
        for (int i = 0; i <= ub; i++)
            ans += calc(num, pos + 1, tight & (i == ub), leading & (i == 0), i);
    } else {
        for (int i = 0; i <= ub; i++)
            if (i != last)
                ans += calc(num, pos + 1, tight & (i == ub), 0, i);
    }
    return res = ans;
}

int helper(string num) {
    memset(dp, -1, sizeof(dp));
    return calc(num, 0, 1, 1, 10);
}

void test_case() {
    int l, r;
    cin >> l >> r;
    cout << (helper(to_string(r)) - helper(to_string(l - 1))) << "\n";
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    test_case();
    return 0;
}