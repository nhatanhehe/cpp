#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, t;
    long long k;
    if(!(cin >> n >> t >> k)) return 0;
    vector<long long> a(n);
    for(int i=0;i<n;++i) cin >> a[i];

    // counts of residues 0,1,2
    int c[3] = {0,0,0};
    for(int i=0;i<n;++i) c[ a[i] % 3 ]++;

    if(c[1]==0 && c[2]==0){
        cout << 0 << "\n";
        return 0;
    }
    if(t > n){
        cout << -1 << "\n";
        return 0;
    }

    int d = (int)((k - 1) % 3);
    if(d < 0) d += 3;

    // dist[c1][c2] = min ops to reach state with c1 items residue 1 and c2 items residue 2
    const int INF = 1e9;
    vector<int> dist((n+1)*(n+1), INF);
    auto idx = [&](int c1, int c2){ return c1*(n+1) + c2; };

    int start_c1 = c[1], start_c2 = c[2];
    queue<pair<int,int>>q;
    dist[idx(start_c1,start_c2)] = 0;
    q.push({start_c1, start_c2});

    while(!q.empty()){
        auto [c1, c2] = q.front(); q.pop();
        int curDist = dist[idx(c1,c2)];
        int c0 = n - c1 - c2;
        // enumerate how many chosen from each residue class
        int max_x0 = min(c0, t);
        for(int x0 = 0; x0 <= max_x0; ++x0){
            int max_x1 = min(c1, t - x0);
            for(int x1 = 0; x1 <= max_x1; ++x1){
                int x2 = t - x0 - x1;
                if(x2 < 0 || x2 > c2) continue;
                // try special in class j where xj > 0
                for(int j = 0; j < 3; ++j){
                    int xj = (j==0?x0 : (j==1?x1 : x2));
                    if(xj == 0) continue;
                    // compute new counts
                    int nx0 = c0, nx1 = c1, nx2 = c2;
                    // remove chosen
                    nx0 -= x0; nx1 -= x1; nx2 -= x2;
                    // for each class r: one special if j==r gets +d, the others get +2
                    // r = 0
                    {
                        int special = (j==0)?1:0;
                        int other = x0 - special;
                        int to_special = (0 + d) % 3;
                        int to_other = (0 + 2) % 3;
                        if(to_special == 0) nx0 += special;
                        else if(to_special == 1) nx1 += special;
                        else nx2 += special;
                        if(to_other == 0) nx0 += other;
                        else if(to_other == 1) nx1 += other;
                        else nx2 += other;
                    }
                    // r = 1
                    {
                        int special = (j==1)?1:0;
                        int other = x1 - special;
                        int to_special = (1 + d) % 3;
                        int to_other = (1 + 2) % 3;
                        if(to_special == 0) nx0 += special;
                        else if(to_special == 1) nx1 += special;
                        else nx2 += special;
                        if(to_other == 0) nx0 += other;
                        else if(to_other == 1) nx1 += other;
                        else nx2 += other;
                    }
                    // r = 2
                    {
                        int special = (j==2)?1:0;
                        int other = x2 - special;
                        int to_special = (2 + d) % 3;
                        int to_other = (2 + 2) % 3;
                        if(to_special == 0) nx0 += special;
                        else if(to_special == 1) nx1 += special;
                        else nx2 += special;
                        if(to_other == 0) nx0 += other;
                        else if(to_other == 1) nx1 += other;
                        else nx2 += other;
                    }
                    // new state's c1', c2'
                    int nc1 = nx1, nc2 = nx2;
                    if(nc1 < 0 || nc2 < 0 || nx0 < 0) continue; // safety
                    int id = idx(nc1, nc2);
                    if(dist[id] == INF){
                        dist[id] = curDist + 1;
                        q.push({nc1, nc2});
                    }
                } // end special j
            }
        }
    } // end BFS

    int ans = dist[idx(0,0)];
    if(ans == INF) cout << -1 << "\n";
    else cout << ans << "\n";
    return 0;
}
