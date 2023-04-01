#pragma GCC target ("avx2")
#pragma GCC optimize("Ofast") 
// Not always a good idea
// #pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << "'" << x << "'";}
void __print(const char *x) {cerr << '"' << x << '"';}
void __print(const string &x) {cerr << '"' << x << '"';}
void __print(bool x) {cerr << x;}
// void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}


typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tpi;
typedef tuple<ll, ll, ll> tpll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<long long> vll;
typedef vector<vector<ll> > vvll;
typedef vector<bool> vb;
typedef long double ld;

#define testcases() int testcases; cin >> testcases; while(testcases--) solve()
#define lsone(S) ((S) & -(S))
int msone(int s) {return 1 << (31 - __builtin_clz(s));}
ll msone(ll s) {return 1ll << (63 - __builtin_clzll(s));}
#define mod(n, m) (((m) + ((n) % (m))) % (m))
#define MOD 1e9+7

// Debug Toggle
// #define ONLINE_JUDGE 0

#ifndef ONLINE_JUDGE
#define deb(x...) cerr << "[" << #x << "] = ["; _print(x)
#define adeb()
#else
#define deb(x...)
#endif

// Variables



// Solve
void solve(){
    
}

// Main
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    // cout.precision(17);

    // testcases();
    solve();
    
    return 0;
}

// TYPE THE ABOVE IN WHEN YOU ARE PREPPING

// FENWICK

#define LSOne(S) ((S) & -(S))

class FenwickTree{
private:
        vector<long long> ft;
public:
    FenwickTree(int m){
        ft.assign(m+1, 0);
    }
    void build(const vector<long long> &freq){
        int m = freq.size()-1;
        ft.assign(m+1, 0);
        for(int i = 1; i <= m;++i){
            ft[i] += freq[i];
             if((i+LSOne(i)) <= m){
                 ft[i+LSOne(i)] += ft[i];
             }
        }
    }

    FenwickTree(const vector<long long> &freq){
        build(freq);
    }
    
    FenwickTree(int m, const vector<int> &data){
        vector<long long> frequency(m+1, 0);
        for(const auto& item : data){
            frequency[item]++;
        }
        build(frequency);
    }

    long long rsq(int i){
        long long sum = 0;
        while(i){
            sum+= ft[i];
            i -= LSOne(i);
        }
        return sum;
    }

    long long rsq(int s, int f){
        return rsq(f) - rsq(s-1);
    }

    void update(int i, int v){
        while(i < ft.size()){
            ft[i] += v;
            i += LSOne(i);
        }
    
    int select(long long k){
        // Find the smallest i such that the culmitive frequency up to and including i is greater than or equal to k
        int i=0;
        int p=1;
        while(p * 2 < ft.size()){
            p *= 2;
        }

        while(p){
            if(k > ft[i+p]){
                k -= ft[i+p];
                i += p;
            }
            p /= 2;
        }
        return i+1;
    }
};

class FenwickRUPQ{ // Index 0 not used
private:
    vector<long long> ft;
    void baseupdate(int i, int v){
        while(i < ft.size()){
            ft[i] += v;
            i += LSOne(i);
        }
    }
public:
    FenwickRUPQ(int m){
        ft.assign(m+1, 0);
    }
    long long val(int i){
        long long sum = 0;
        while(i){
            sum+= ft[i];
            i -= LSOne(i);
        }
        return sum;
    }
    void update(int s, int f, int v){
        baseupdate(s, -v);
        baseupdate(f+1, v);
    }
};

// STRING HASHING

class StringHash{
private:
    const long long P=9973, M;
    // Hash array is a prefix sums (1 indexed)
    vector<long long> pow, hash;
public:
    StringHash(const string& s, const long long &M): pow(s.size()+1), hash(s.size()+1), M(M){
        const int n = s.size();
        pow[0] = 1;
        hash[0] = 0;
        for(int i=1;i<=n;++i){
            pow[i] = (pow[i-1] * P) % M; 
            hash[i] = ((hash[i-1] * P) % M + s[i-1]) % M;
        }
    }

    // S and F are 0 indexed and inclusive
    long long get_hash(int s, int f){
        long long ret = hash[f+1] - (hash[s] * pow[f-s+1]);
        return (ret % M + M) % M;
    }
};


// LCA


class SparseTable{
private:
    const int n;
    int k;
    vector<vi> st;
    vi logs;

    // Can modify to min
    int f(int i, int j){
        return min(i, j);
    }

public:
    SparseTable(const vi& a): n(a.size()){
        st.resize(n);
        logs.reserve(n+1);

        // Compute logs
        logs[1] = 0;
        for(int i=2;i<=n;++i){
            logs[i] = logs[i/2] + 1;
        }

        k = logs[n] + 2; 

        // Init array
        for(int i=0;i<n;++i){
            st[i].resize(k);
            st[i][0] = a[i];
        }

        // Precalculate values
        for(int i=1;i<k;++i){
            for(int j=0;j + (1 << i) <= n;++j){
                st[j][i] = f(st[j][i-1], st[j + (1 << (i-1))][i-1]);
            }
        }
    }

    // s and f are inclusive
    int query(int l, int r){
        int clog = logs[r - l + 1];
        return f(st[l][clog], st[r - (1 << clog) + 1][clog]);
    }
};


// Variables

// Build sparse table off euler_tour
void dfs(int node = 0, int parent = -1) {

	tin[node] = timer; // The time when we first visit a node

	euler_tour[timer++] = node;

	for (int i : graph[node]) {

		if (i != parent) {

			dfs(i, node);

			euler_tour[timer++] = node;

		}

	}

}

int lca(int a, int b) {

	if (tin[a] > tin[b]) swap(a, b);

	return query(tin[a], tin[b]);

}



// b^p (mod m)
// Time Complexity O(log p)
long long power(long long b, long long p, long long m){
    long long result = 1;
    b %= m;
    while(p > 0){
        // If p is odd
        if(p & 1){ // binary operation shorthand
            result = (result * b) % m;
        } // don't bother with p--

        p = p >> 1; // Same as dividing by 2 but faster
        b = (b * b) % m;
    }
    return result;
}

// Fermat's Little Theorm modInverse
// Time Complexity O(log p)
// First ensure that they're coprime and m is a prime
long long modInversePrime(long long x, long long m){
    return power(x, m-2, m);
}


// Not 100% sure it's bug free, double check
vi merge_sort(vi& arr, int s, int f, ll& inv){
    if(s == f){
        vi ret = {arr[s]};
        return ret;
    }
    int mid = s + (f - s)/2;
    vi v1 = merge_sort(arr, s, mid, inv);
    vi v2 = merge_sort(arr, mid+1, f, inv);
    int n = f-s+1;
    ll s1 = v1.size(), s2 = v2.size();
    vi ret(n);
    ll p1=0, p2=0;
    for(int i=0;i<n;++i){
        if((p2 == s2 or v1[p1] <= v2[p2]) and p1 != s1){
            ret[i] = v1[p1];
            p1++;
        }
        else{
            ret[i] = v2[p2];
            p2++;
            inv += s1 - p1;
        }
    }
    return ret;
}


// OST EXAMPLE

#include <bits/extc++.h>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OrderStatistics;

// Solve
void solve(){
    int n;
    cin >> n;

    OrderStatistics tree;
    // unordered_set<int> s;
    vll ans(n+1);
    // vi a(n);
    // vi freq(n+1);
    vvi temp(n+1);
    for(int i=0;i<n;++i){
        // cin >> a[i];
        int x;
        cin >> x;
        temp[x].push_back(i);
        // freq[a[i]]++;
        
        // // if(s.find(a[i]) != s.end()){
        // //     deb(tree.order_of_key(a[i]));
        // //     ans[a[i]] += i - 1 - tree.order_of_key(a[i]);
        // //     tree.insert(a[i]);
        // //     continue;
        // // }
        // // s.insert(a[i]);
        // cccc
        // deb(tree.order_of_key(a[i])); - 11
    }
    for(int i=n;i>=0;--i){
        int m = temp[i].size();
        for(int j=m-1;j>= 0;--j){
            tree.insert(temp[i][j]);
            ans[i] += tree.order_of_key(temp[i][j]);
        }
    }

    cout << "0\n";
    ll prev = 0;
    for(int i=0;i<n-1;++i){
        prev += ans[i];
        // deb(ans[i]);
        cout << prev << '\n';
    }

}

class SegmentTree {                              // OOP style
private:
  int n;                                         // n = (int)A.size()
  vi A, st, lazy;                                // the arrays

  int l(int p) { return  p<<1; }                 // go to left child
  int r(int p) { return (p<<1)+1; }              // go to right child

  int conquer(int a, int b) {
    if (a == -1) return b;                       // corner case
    if (b == -1) return a;
    return min(a, b);                            // RMQ
  }

  void build(int p, int L, int R) {              // O(n)
    if (L == R)
      st[p] = A[L];                              // base case
    else {
      int m = (L+R)/2;
      build(l(p), L  , m);
      build(r(p), m+1, R);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }

  void propagate(int p, int L, int R) {
    if (lazy[p] != -1) {                         // has a lazy flag
      st[p] = lazy[p];                           // [L..R] has same value
      if (L != R)                                // not a leaf
        lazy[l(p)] = lazy[r(p)] = lazy[p];       // propagate downwards
      else                                       // L == R, a single index
        A[L] = lazy[p];                          // time to update this
      lazy[p] = -1;                              // erase lazy flag
    }
  }

  int RMQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return -1;                        // infeasible
    if ((L >= i) && (R <= j)) return st[p];      // found the segment
    int m = (L+R)/2;
    return conquer(RMQ(l(p), L  , m, i          , min(m, j)),
                   RMQ(r(p), m+1, R, max(i, m+1), j        ));
  }

  void update(int p, int L, int R, int i, int j, int val) { // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return;
    if ((L >= i) && (R <= j)) {                  // found the segment
      lazy[p] = val;                             // update this
      propagate(p, L, R);                        // lazy propagation
    }
    else {
      int m = (L+R)/2;
      update(l(p), L  , m, i          , min(m, j), val);
      update(r(p), m+1, R, max(i, m+1), j        , val);
      int lsubtree = (lazy[l(p)] != -1) ? lazy[l(p)] : st[l(p)];
      int rsubtree = (lazy[r(p)] != -1) ? lazy[r(p)] : st[r(p)];
      st[p] = (lsubtree <= rsubtree) ? st[l(p)] : st[r(p)];
    }
  }

public:
  SegmentTree(int sz) : n(sz), st(4*n), lazy(4*n, -1) {}

  SegmentTree(const vi &initialA) : SegmentTree((int)initialA.size()) {
    A = initialA;
    build(1, 0, n-1);
  }

  void update(int i, int j, int val) { update(1, 0, n-1, i, j, val); }

  int RMQ(int i, int j) { return RMQ(1, 0, n-1, i, j); }
};



class UnionFind{
private:
    vector<int> parent, rank;

    // Optional: Set Size
    vector<int> setSize;

    // Optional: Set Count
    int setCount;
public:
    UnionFind(int size){
        for(int a=0;a<size;++a){
            parent.push_back(a);
            rank.push_back(0);

            // Optional: Set Size
            setSize.push_back(1);
        }
        
        // Optional: Set Count
        setCount = size;
    }

    // Optional: Add Item
    void addItem(){
        parent.push_back(parent.size());
        rank.push_back(0);

        // Optional: Set Size
        setSize.push_back(1);

        // Optional: Set Count
        setCount++;
    }

    int findSet(int i){
        vector<int> condense;
        while(parent[i] != i){
            condense.push_back(i);
            i = parent[i];
        }
        for(auto &x:condense){
            parent[x] = i;
        }
        return i;
    }
    bool sameSet(int x1, int x2){
        return findSet(x1) == findSet(x2);
    }

    // Optional: Set Count
    int getSetCount(){
        return setCount;
    }

    // Optional: Set Size
    int getSetSize(int x){
        return setSize[findSet(x)];
    }

    void unionSet(int x1, int x2){
        if(sameSet(x1, x2)){
            return;
        }
        int tp1 = findSet(x1);
        int tp2 = findSet(x2);

        if(rank[tp1] > rank[tp2]){
            swap(tp1, tp2);
        }
        parent[tp1] = tp2;
        rank[tp2]++;

        // Optional: Set Size
        setSize[tp2] += setSize[tp1];

        // Optional: Set Count
        setCount--;
    }
};


