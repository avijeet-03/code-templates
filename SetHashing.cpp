#include "bits/stdc++.h"
using namespace std;
#define int long long

int power(int a, int b, int m) {
    int res = 1;
    while (b) {
        if (b % 2)
            (res *= a) %= m;
        (a *= a) %= m;
        b /= 2;
    }
    return res;
}

class Hashing {
    int k, h, m;

public:
    Hashing() {
        k = 998998991; // any large random value
        m = 999999929; // carefully select any large prime, not so popular
        h = 61; // generally smaller than 100
    }

    int getHashValue(int x) {
        return power(x + k, h, m);
    }

    int addHashValue(int a, int b) {
        return (a + b) % m;
    }

    int removeHashValue(int a, int b) {
        return (a - b + m) % m;
    }

    bool equals(int a, int b) {
        return (a % m) == (b % m);
    }
};

void test_case() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];

    Hashing hashing;
    // build a prefix sum array of hash values
    a[0] = hashing.getHashValue(a[0]);
    b[0] = hashing.getHashValue(b[0]);
    for (int i = 1; i < n; i++) {
        a[i] = hashing.addHashValue(a[i - 1], hashing.getHashValue(a[i]));
        b[i] = hashing.addHashValue(b[i - 1], hashing.getHashValue(b[i]));
    }

    while (q--) {
        int la, ra, lb, rb;
        cin >> la >> ra >> lb >> rb;
        la--, ra--, lb--, rb--;

        int firstHashValue = a[ra];
        if (la > 0)
            firstHashValue = hashing.removeHashValue(firstHashValue, a[la - 1]);

        int secondHashValue = b[rb];
        if (lb > 0)
            secondHashValue = hashing.removeHashValue(secondHashValue, b[lb - 1]);

        if (hashing.equals(firstHashValue, secondHashValue))
            cout << "Yes" << "\n";
        else
            cout << "No" << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    test_case();
    return 0;
}

// Problem Link: https://atcoder.jp/contests/abc367/tasks/abc367_f