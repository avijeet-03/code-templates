//++++++++++++++++++++++++++++++++++++++

// calculating mod
//If you're adding a + b and (a < mod and b < mod), then (a+b) % mod is equivalent to
const int mod = 1e9 + 7;
int c = a + b;
if  (c >= mod) c -= mod;
//Given the slow nature of mod and java this will really help you squeeze under time limit

//++++++++++++++++++++++++++++++++++++++
//FASTEST FIBONNACI
const int mod = 1e9 + 7;
unordered_map<int, int> mp;
// fib(0) = 1, fib(1) = 1, fib(2) = 2, fib(3) = 3
int fib(int n)
{
    // Calculates (n + 1)th Fibonacci Number
    if (n < 2)
        return 1;
    if ( mp.find(n) != mp.end())
        return mp[n];
    mp[n] = ( fib((n + 1) / 2) * fib(n / 2) + fib((n - 1) / 2) * fib((n - 2) / 2) ) % mod;
    return mp[n];
}

//+++++++++++++++++++++++++++++++++++++++

// Handling with angles
#define PI 3.14159265358
#define radianstodegrees(R)((180.0 * R) / PI)

// computes the angle projected at origin by a point
double computeAngle(int i, int j) {
    double p = j * 1.0;
    double q = i * 1.0;
    double angle = atan2(p, q);
    return radianstodegrees(angle);
}

// ++++++++++++++++++++++++++++++++++++++

// SEIVE OF ERATOSTHNES
int N = 1e6;
vector<bool> isPrime(N + 1, true);
// Marks all the prime numbers
void seive() {
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= N; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= N; j += i)
                isPrime[j] = false;
        }
    }
}
// ++++++++++++++++++++++++++++++++++++++
// Linear Seive
const int N = 1e6;
vector<int> lp(N + 1);
vector<int> prime;
void seive() {
    for (int i = 2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            prime.push_back (i);
        }
        for (int j = 0; j < (int)prime.size() && prime[j] <= lp[i] && i * prime[j] <= N; ++j)
            lp[i * prime[j]] = prime[j];
    }
}
// ++++++++++++++++++++++++++++++++++++++
/*
    Seive function taken from
    Source: https://github.com/mejibyte/competitive_programming/blob/
    master/lib/Documentation/9thinksYouNeed-ACMSolver/sieve%20by%20yarin.cpp
*/
// Super fast & Memory-tight Sieve by Yarin
#define MAXSIEVE 100000000 // All prime numbers up to this 
#define MAXSIEVEHALF (MAXSIEVE/2)
#define MAXSQRT 5000 // sqrt(MAXSIEVE)/2 
char a[MAXSIEVE / 16 + 2];
#define isprime(n) (a[(n)>>4]&(1<<(((n)>>1)&7))) // Works when n is odd 

//have to check for even numbers
void seive()
{
    int i, j;
    memset(a, 255, sizeof(a));
    a[0] = 0xFE;
    for (i = 1; i < MAXSQRT; i++)
        if (a[i >> 3] & (1 << (i & 7)))
            for (j = i + i + i + 1; j < MAXSIEVEHALF; j += i + i + 1)
                a[j >> 3] &= ~(1 << (j & 7));
}
//++++++++++++++++++++++++++++++++++++++
// Euler Totient Function
int N = 1e6;
vector<int> phi(N + 1);
void euler_totient_function() {
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= N; i++)
        phi[i] - i - 1;

    for (int i = 2; i <= N; i++)
        for (int j = 2 * i; j <= N; j++)
            phi[j] -= phi[i];
}
// ++++++++++++++++++++++++++++++++++++++
int power(int a, int b)         // Binary Exponentiation
{   // O(log b) time
    int result = 1;
    while (b)
    {
        if (b % 2)
            (result *= a) %= mod;
        (a *= a) %= mod;
        b /= 2;
    }
    return result;
}
//+++++++++++++++++++++++++++++++++++++++
bool check(int mid, int a, int b) {
    int curr = 1;
    while (curr <= a and b) {
        curr *= mid;
        b--;
    }
    return curr <= a;
}

int root(int a, int b) {
    // returns the bth root of a
    int res = 0;
    int low = 0, high = a;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid, a, b)) {
            res = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return res;
}
// ++++++++++++++++++++++++++++++++++++++
// Modular Multiplicative inverse
int inverse(int a) {
    return power(a, mod - 2);
}

// Computing Binomial Coefficient nCr
const int MAXN = 1e5 + 5;
vector<int> factorial(MAXN + 1);
void precal() {
    factorial[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        factorial[i] = factorial[i - 1] * i % mod;
}
int nCr(int n, int k)
{
    return factorial[n] * inverse(factorial[k] * factorial[n - k] % mod) % mod;
}
int solve(int n, int r) { // ncr when n is very large n < 1e9
    if (r > n / 2)
        r = n - r;
    int res = 1;
    for (int i = 1; i <= r; i++)
        (res *= (n - i + 1)) %= mod;
    for (int i = 1; i <= r; i++)
        (res *= inverse(i)) %= mod;
    return res;
}
// ++++++++++++++++++++++++++++++++++++++
// Counting nCr avoiding overflows
int nCr(int n, int r) {
    if (n < 0 or r < 0 or r > n)
        return 0;
    int res = 1;
    for (int i = 1; i <= r; i++) {
        res *= (n + 1 - i);
        res /= i;
    }
    return res;
}
// ++++++++++++++++++++++++++++++++++++++
// CATALAN Number
int N = 1e6 + 1;
vector<int> catalan(N + 1);
void catalan_function() {
    catalan[0] = catalan[1] = 1;
    for (int i = 2; i <= n; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++) {
            catalan[i] += (catalan[j] * catalan[i - j - 1]) % mod;
            if (catalan[i] >= mod)
                catalan[i] -= mod;
        }
    }
}
// ++++++++++++++++++++++++++++++++++++++
// POWER OF 2
bool is_powerof2(int n)
{
    return ((n & n - 1) == 0);
}
//+++++++++++++++++++++++++++++++++++++++
// GCD
int gcd(int a, int b)
{
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
// inbuilt function for gcd
__gcd(a, b);
// in C++17 we can use
lcm(a, b); // to find the lcm of two numbers
// ++++++++++++++++++++++++++++++++++++++
// Extended Euclidean algorithm
// a * x + b * y = gcd(a, b)
// It will return gcd(a, b) and store the values of x and y
int extended_euclidean_algorithm_gcd(int a, int b, int &x, int &y)
{
    x = 1, y = 0;
    int x1 = 0, y1 = 1;
    while (b) {
        int q = a / b;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a, b) = make_tuple(b, a - q * b);
    }
    return a;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++

// Z - function
// z[i] is the longest string that is at the same time a prefix
// of s and a prefix of the suffix starting at i
vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++

// custom priority queue
struct item {
    int value;
    int row;
    int col;
    item (int value, int row, int col) : value(value), row(row), col(col) {

    }
};

struct cmp {
    bool operator() (item const &x, item const &y) const {
        return x.value > y.value;
    }
};

priority_queue<item, vector<item>, cmp> pq;
// lowest a.value will be on top
// everything works opposite for priority queue in c++

// +++++++++++++++++++++++++++++++++++++++++++++++++
// DISJOINT SET UNION
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

    int getSize(int u) {
        return sz[find_parent(u)];
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
// ++++++++++++++++++++++++++++++++++++++

// PBDS
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>,
                         rb_tree_tag, tree_order_statistics_node_update>;

// ++++++++++++++++++++++++++++++++++++++
/*
   Idea taken from:
   https://leetcode.com/problems/count-of-smaller-numbers-after-self/
   discuss/1298870/BST-Approach-(Fully-Explained)-Cpp-Solution
   returns number of elements smaller on right side
*/
struct Node {
    int data;
    struct Node *left, *right;
    int lc;
    Node(int data) {
        this->data = data;
        left = right = NULL;
        lc = 0;
    }
};

int insert(struct Node *node, int key) {
    struct Node *r = NULL, *p;
    int c = 0;

    while (node != NULL) {
        r = node;
        if ( (node->data) >= key)
        {
            node->lc = (node->lc) + 1;
            node = node->left;
        }
        else {
            c += 1 + (node->lc);
            node = node->right;
        }
    }
    p = new Node(key);
    if (p->data <= r->data)
        r->left = p;
    else
        r->right = p;
    return c;
}

vector<int> countSmallerOnRight(vector<int> &nums) {
    int n = nums.size();
    vector<int> vect(n, 0);

    int j = 1;
    while (j < n && nums[j - 1] <= nums[j]) j++;
    if (j == n) return vect;
    j = n - 2;
    while (j > -1 && nums[j] >= nums[j + 1]) {
        if (nums[j] > nums[j + 1])
            vect[j] = n - j - 1;
        if (nums[j] == nums[j + 1]) vect[j] = vect[j + 1];
        j--;
    }
    if (j == -1) return vect;
    struct Node *root = new Node(nums[n - 1]);
    for (int i = n - 2; i > -1; i--)
        vect[i] = insert(root, nums[i]);

    return vect;
}

// ++++++++++++++++++++++++++++++++++++++

Useful functions like any_of(), all_of(), none_of(), count()

-> std::any_of
This is a very useful function that returns true iff any of the elements in the range [first, last) satisfies some condition.
Lets say you want to figure out if an array contains at least one 9. You could just write the naive loop and waste time in contest.

bool ok = 0;
for (int i = 0; i < (int)(a).size(); ++i) {
    if (a[i] == 9) {
        ok = 1;
        break;
    }
}
but you could be smart and write this all in one line.

bool ok = any_of(a.begin(), a.end(), [](int x) { return x == 9; });


-> std::all_of
This is another useful function that functions similar to std::any_of. The difference is that it returns true iff all the elements in the range [first, last) follow some condition.
Lets say you want to find if the array consists of all 9s.

bool ok = 1;
for (int i = 0; i < (int)(a).size(); ++i) {
    if (a[i] != 9) {
        ok = 0;
    }
}
Now this method saves a couple of lines which means that you will get the fastest submit time. Guranteed or I will give you your money back. : D

bool ok = all_of(a.begin(), a.end(), [](int x) { return x == 9; });


->std::none_of
This is yet another function that is close relatives of the two mentioned above. This function returns true iff all the elements does not follow some condition.
Lets say you want to find if the array doesnt contain 9.

Noobs will do:

    bool ok = 1;
for (int i = 0; i < (int)(a).size(); ++i) {
    if (a[i] == 9) {
        ok = 0;
    }
}
Pros would do:

    bool ok = none_of(a.begin(), a.end(), [](int x) { return x == 9; });


-> std::count
This functions counts the number of elements in the range [first, last) that are equal to some variable val.

Noobinho:

int cnt = 0;
for (int i = 0; i < (int)(a).size(); ++i) {
    cnt += (a[i] == x);
}
Proinho:
int cnt = count(a.begin(), a.end(), x);


-> std::find
This function returns the first iterator that compares equal to val.

Nubs:

int hld = -1;
for (int i = 0; i < (int)(a).size(); ++i) {
    if (a[i] == x) {
        hld = i;
        break;
    }
}
Prubs:
int hld = find(a.begin(), a.end(), x) - a.begin();
// ++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++++++++++++++
// A good technique for binary search
A good technique:

if you are looking for 1st position satisfying some condition do this:

        mid = (left + right) / 2;

if (some_condition()) left = mid + 1;

else right = mid;

if you are looking for last position satisfying some condition do this:

        mid = (left + right + 1) / 2;

if (some_condition()) left = mid;

else right = mid - 1;

// +++++++++++++++++++++++++++++++++++++++
// Effective debugging templates

void __print(int x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

// +++++++++++++++++++++++++++++++++++++++