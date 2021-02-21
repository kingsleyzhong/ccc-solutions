// Total Formula: Total = M (amount of rows) X C (column (up-down) strokes) + N (amount of columns) * R (row (left-right) strokes) - 2 * R * C


#include <bits/stdc++.h> // Includes all header files

using namespace std; // std::cout 

int main(){
    ios_base::sync_with_stdio(false); // Fast I/O
    cin.tie(nullptr);
    cout.tie(nullptr);

    long long m, n;
    cin >> m >> n;

    int k;
    cin >> k;

    unordered_set<int> lr; // R
    unordered_set<int> ud; // C

    for(int a=0;a<k;++a){
        char c;
        int x;
        cin >> c >> x;
        if(c == 'R'){
            //lr
            if(lr.find(x) == lr.end()){
                lr.emplace(x);
            }
            else{
                lr.erase(x);
            }
        }
        else{
            //c == C
            // up down
            if(ud.find(x) == ud.end()){
                ud.emplace(x);
            }
            else{
                ud.erase(x);
            }
        }
    }

    long long total = 0;

    // Total Formula: Total = M (amount of rows) X C (column (up-down) strokes) + N (amount of columns) * R (row (left-right) strokes) - 2 * R * C

    total += (long long)m*ud.size();
    total += (long long)n*lr.size();
    total -= (long long)2*ud.size() * lr.size();

    cout << total;
    
    return 0;
}