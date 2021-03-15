/*
Things to Notice + Ideas:

- When you get off the subway you won't get back on.
- The walkways never change... so each day your route will be TAKE TRAIN or TAKE TRAIN AND WALK TO N.
- What that tells us is that we can split up this problem into 2 parts, one is calculating walkway distance which will never change and the other is calulating the distance for each day. Note that you only need to change 2 things each day because all you're doing is swapping stations.


WATCH YOUTUBE VIDEO FOR FULL EXPLANATION

I'm 1-indexing everything because it's much easier to work with.
*/


#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, w, d; // Stations, Walkways, Days
    cin >> n >> w >> d;

    // Adjacency List for WALKWAYS
    vector<int> al[n+1];
    int wdist[n+1]; // Distance from each station to station N through walkways. Distance = 10^9 (Infinity) if un-reachable (the algorithm later on will not consider something that large as we're minimizing time)
    for(int a=1;a<n;++a){
        wdist[a] = 1e9; // Default everything is unreachable
    }
    wdist[n] = 0; // You're already at the target station

    // Getting Walkway Input
    for(int a=0;a<w;++a){
        int from, to;
        cin >> from >> to;
        al[to].push_back(from); // This is reversed as we're running a reverse BFS from N to see how far each station is.
    }

    //BFS on station walking distances: Read up on Breath First Search (explained in youtube video)

    bool visited[n+1]; // Boolean array to see if station has already been visited, this is to avoid getting stuck in an infinite loop.
    memset(visited, 0, sizeof visited); // Technically un-needed as boolean array defaults to false but just for safety.
    visited[n] = true; // Start at statio N

    queue<int> q; // Queue for BFS algorithm

    q.push(n); // Starting at station N

    while(!q.empty()){ // Keep iterating through stations until you're done
        int cur_station = q.front();
        q.pop();
        for(const int next_station: al[cur_station]){ // c++ 11 range based for loop through all stations that are reachable from current station
            if(!visited[next_station]){ // Make sure we're not getting stuck in a cycle
                wdist[next_station] = wdist[cur_station] + 1;
                visited[next_station] = true;
                q.push(next_station);
            }
        }
    }

    // Getting the subway line station location
    int subwayline[n+1]; // subwayline[0] is unused, subwayline[1] to subwayline[n] stores the station number at that point

    multiset<int> culdist; // culmitive distance... doesn't matter which station it's from / to all we care about is what the distance is and a multimap is perfect for this.

    // Getting initial subway locations data
    for(int a=1;a<=n;++a){
        cin >> subwayline[a];
        // Subway distance is = index of subwayline -1
        culdist.insert(a-1 + wdist[subwayline[a]]);
        // Distance on train + walking distance 
    }

    // For each "station swap"
    for(int a=0;a<d;++a){
        int station1, station2;
        cin >> station1 >> station2; // Gives station location

        // Get old distance and remove from multiset
        int station1OldDist = station1-1 + wdist[subwayline[station1]];
        int station2OldDist = station2-1 + wdist[subwayline[station2]];
        culdist.erase(station1OldDist);
        culdist.erase(station2OldDist);

        // Swap opreration
        swap(subwayline[station1], subwayline[station2]);

        // Add new distances
        culdist.insert(station1-1 + wdist[subwayline[station1]]);
        culdist.insert(station2-1 + wdist[subwayline[station2]]);

        // Output the minimum distance - multisets are dynamically sorted internally, by taking the first number (derefernce begin iterator) you are getting the smallest distance 
        cout << *culdist.begin() << '\n';
    }
    
    return 0;
}