#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> g(n);
    for (int i = 0; i < n; i++) cin >> g[i];

    vector<vector<bool>> used(n, vector<bool>(n, false));

    vector<pair<int,int>> cur, nxt;
    cur.push_back({0,0});
    used[0][0] = true;

    string ans;
    ans.push_back(g[0][0]);

    for (int step = 2; step <= 2*n-1; step++) {
        nxt.clear();

        char best = 'z' + 1;

        // generate all next possible cells
        for (auto &p : cur) {
            int x = p.first, y = p.second;

            auto relax = [&](int nx, int ny) {
                if (nx >= 0 && ny >= 0 && nx < n && ny < n && !used[nx][ny]) {
                    used[nx][ny] = true;
                    nxt.push_back({nx, ny});
                    best = min(best, g[nx][ny]);
                }
            };

            relax(x+1, y);
            relax(x, y+1);
        }

        // filter only best cells
        vector<pair<int,int>> filtered;
        for (auto &p : nxt) {
            if (g[p.first][p.second] == best)
                filtered.push_back(p);
        }
        cur.swap(filtered);

        ans.push_back(best);
    }

    cout << ans;
}

