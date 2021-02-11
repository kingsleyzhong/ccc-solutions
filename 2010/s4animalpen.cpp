#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
typedef vector<long long> vll;

#define mod(n, m) (((m) + ((n) % (m))) % (m))

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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n;
    cin >> n;
    // Unpaired edges, Format = {Pair of edges (ascending) : NODE, weight}
    map<pii, pair<int, long long> > unpaired;
    vector<tuple<long long, int, int> > edgel; // Vector of edges, format: Weight, node1, node2;

    for(int a=0;a<n;++a){ // input parsing
        int edges;
        cin >> edges;
        int vert[edges];
        // int weight[edges];

        for(int b=0;b<edges;++b){
            cin >> vert[b];
        }
        for(int b=0;b<edges;++b){
            long long weight;
            cin >> weight;
            int v1 = vert[b], v2 = vert[mod(b+1, edges)];
            if(v1 > v2){
                swap(v1, v2);
            }
            pii key = {v1, v2};
            if(unpaired.count(key) == 1){
                auto data = unpaired[key];
                tuple<long long, int, int> edge = {weight, data.first, a};
                edgel.push_back(edge);
                unpaired.erase(key);
            }
            else{
                unpaired[key] = {a, weight};
            }
        }
    }
    // for(auto &entry : unpaired){
    //     cout << entry.first.first << ' ' << entry.first.second << ' ' << entry.second.first << ' ' << entry.second.second << endl;
    // }

    //kruskal's mst algorithm without outside
    sort(edgel.begin(), edgel.end());
    
    UnionFind uf(n);

    long long cost = 0;

    for(auto &dt : edgel){
        long long weight = get<0>(dt);
        int v1 = get<1>(dt);
        int v2 = get<2>(dt);

        if(uf.sameSet(v1, v2)){
            continue;
        }
        else{
            // cout << v1 << ' ' << v2 << ' ' << weight << endl;
            cost += weight;
            uf.unionSet(v1, v2);
        }

        if(uf.getSetCount() == 1){
            break;
        }
    }

    // Adding outside nodes 
    for(const auto &val : unpaired){
        auto data = val.second;
        tuple<long long, int, int> edge = {data.second, data.first, n};
        edgel.push_back(edge);
    }

    // redo mst with outside
    sort(edgel.begin(), edgel.end());
    
    UnionFind ufn(n+1);

    long long costn = 0;

    for(auto &dt : edgel){
        long long weight = get<0>(dt);
        int v1 = get<1>(dt);
        int v2 = get<2>(dt);

        if(ufn.sameSet(v1, v2)){
            continue;
        }
        else{
            costn += weight;
            // cout << v1 << ' ' << v2 << ' ' << weight << endl;
            ufn.unionSet(v1, v2);
        }

        if(ufn.getSetCount() == 1){
            break;
        }
    }

    cout << min(cost, costn);



    
    return 0;
}