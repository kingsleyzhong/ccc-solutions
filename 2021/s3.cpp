#include <bits/stdc++.h>

using namespace std;

vector<int> p, w, d;
int n;

long long move(int x){ // Function that takes the position of the concert and returns time takes for everyone to hear it
    long long time= 0;
    for(int a=0;a<n;++a){ // Loop through each friend
        int rnl = p[a]-d[a]; // Left and right hearing range
        int rnr = p[a]+d[a];

        // Check if the friend can already hear concert
        if(x >= rnl and x <= rnr){
            continue;
        }
        int close = rnr;
        if(abs(x-rnl) < abs(x-rnr)){
            close = rnl;
        }

        time  += (long long)w[a] * abs(x-close);
    }
    return time;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    

    // Get input
    cin >> n;
    
    p.resize(n);
    w.resize(n);
    d.resize(n);

    int l = 1e9;
    int r = 0;

    for(int a=0;a<n;++a){
        cin >> p[a] >> w[a] >> d[a];
        l = min(l, p[a]);
        r = max(r, p[a]);
    }


    // Ternary Search for Function Minimum

    long long best = 1e18;
    for(int a=0;a<60;++a){
        int delta = (r-l)/3;
        int m1 = l+delta;
        int m2 = r-delta;
        long long x1 = move(m1);
        long long x2 = move(m2);
        best = min(x1, best);
        best = min(x2, best);
        if(x1 > x2){
            l = m1;
        }
        else{
            r = m2;
        }
    }

    cout << best  << endl;
    
    return 0;
}


