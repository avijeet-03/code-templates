#include "bits/stdc++.h"
using namespace std;
#define int long long

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using ordered_set = tree<int, null_type, less<int>,
      rb_tree_tag, tree_order_statistics_node_update>;

/*
    i) s.order_of_key(x) - counts the number of elements in the set
                that are strictly less than x
    ii) s.find_by_order(k) - returns the iterator corresponding to the
                        kth lowest element in the set (0-indexed);
*/

/*
    #define int long long gives compilation error
*/

// for custom comparators we can use a struct and
// overload the operator ()
/*
template <class T>
struct comp_fx
{
    bool operator()(const T &a, const T &b)
    {

        return a < b;
    }
};

*/

// rest of my code template