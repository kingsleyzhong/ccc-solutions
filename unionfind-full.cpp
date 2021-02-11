/*
Union Find Disjoint Set Data Structure

Most useful for Krukal's MST Algorithm
*/



#include <vector>
using namespace std;


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
