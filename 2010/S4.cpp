/*
Hint 0:
It really doesn't matter what the pen / farm looks like (like don't bother with finding stuff like area, angles and plotting it). I'm pretty sure it won't be a legal euclidian geometric shape for some test cases.

Hint 1:
It doesn't matter where the animals meet, they all pens just must be connected
Hint 2:
Could the connection between the pens be represented as a graph?
Hint 3:
A modified lowest edge cost greedy will work

The solution is: Parsing data into a graph, running minimum spanning tree twice (once with outside and once without) and outputting min.

Why does this work? For the animals to meet up, they must all be connected. There are two cases as there isn't animals on the outside (doesn't need to be connected) but sometimes it's cheaper to include the "outside".

The MST Algorithm that I'm using is Kruskal's algorithm (with UFDS data structure). 

*/


#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
typedef vector<long long> vll;

// This gives positive modulo to avoid getting something like 4%5 = -1 and getting a segmentation fault for accessing out of bounds array
#define mod(n, m) (((m) + ((n) % (m))) % (m)) 

class UnionFind{ // UnionFind Data Structure, you can find it in the main folder of this repository
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
    // Unpaired edges, Format = {Corner 1, Corner 2 (ascending)}:{Node #, Weight}
    // Pretty complex data structure, keeping track of unpaired edges... every bit of data is needed for the paring process.
    map<pii, pair<int, long long> > unpaired; //map is slower than unordered_map but it is fast enough and you don't have to deal with writing your own hash function
    vector<tuple<long long, int, int> > edgel; // Vector of edges, format: Weight, node1, node2;
    
    // Weight has to be first so that we can use the built in sort without having to write our own.
    
    // Node isn't given but it is assigned to as the first pen is given node number 0.
    
    
    /*
    Basically the way that the input is parsed is we get the number of edges.
    For each weight we first determine which 2 corners it belongs to (details in problem specs). Then we form a key
    to the unpaired map. We check if this unpaired edge is in the map, if it isn't we add it to the map. If it is we 
    remove that key from the map and form a edge to be added to edgel.
    
    */

    for(int a=0;a<n;++a){ // input parsing (a is the node number)
        int edges;
        cin >> edges; // # of corners is the same as the number of edges in a polygon
        int vert[edges]; // Vert is just the corners
        
        for(int b=0;b<edges;++b){
            cin >> vert[b];
        }
        for(int b=0;b<edges;++b){
            long long weight;
            cin >> weight;
            int v1 = vert[b], v2 = vert[mod(b+1, edges)]; // Problem statement tells you how to do this
            if(v1 > v2){ // Keep ascending order for matching
                swap(v1, v2);
            }
            pii key = {v1, v2};
            if(unpaired.count(key) == 1){ // It is found in map
                auto data = unpaired[key]; // Find the other unpaired key
                tuple<long long, int, int> edge = {weight, data.first, a}; // Weight, the other node# and this node#
                edgel.push_back(edge);
                unpaired.erase(key);
            }
            else{
                unpaired[key] = {a, weight}; //a is current node
            }
        }
    }

    //kruskal's mst algorithm without outside
    // Google Kruskasl's MST algorithm for explanation
    sort(edgel.begin(), edgel.end());
    
    // Sorts by weight ascending first, then node1 then node 2
    
    UnionFind uf(n);

    long long cost = 0;

    for(auto &dt : edgel){ // c++ 11 style
        long long weight = get<0>(dt);
        int v1 = get<1>(dt);
        int v2 = get<2>(dt); // Dealing tuples

        if(uf.sameSet(v1, v2)){
            continue;
        }
        else{
            cost += weight;
            uf.unionSet(v1, v2);
        }

        if(uf.getSetCount() == 1){
            break;
        }
    }

    
    // now we do the second case with adding outside nodes   
    
    // Adding outside nodes 
    for(const auto &val : unpaired){
        auto data = val.second;
        tuple<long long, int, int> edge = {data.second, data.first, n}; // using n as the outside node number(cuz other nodes go from 0 to n-1). still using format weight, node1, node2
        edgel.push_back(edge);
    }

    // redo mst with outside
    sort(edgel.begin(), edgel.end()); //resort because of extra added edges
    
    UnionFind ufn(n+1); //+1 becasuse of outside

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
            ufn.unionSet(v1, v2);
        }

        if(ufn.getSetCount() == 1){
            break;
        }
    }

    cout << min(cost, costn);



    
    return 0;
}
