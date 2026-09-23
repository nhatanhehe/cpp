#include <bits/stdc++.h>
#define task "chttrip"
#define int long long
#define ll long long
#define ld long double
#define ii pair<int, int>
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define mems(x, y) memset(x, y, sizeof(x));
using namespace std;
const int mod = 1e9 + 7, moi = 2e5 + 9;
const ll INF = 1e18;
const ld EFS = 1e-12;
const int dx[] = { 1, -1, 0, 0};
const int dy[] = { 0, 0, 1, -1};

struct pt {

};

int n, A, B;
ll dp[moi][2];
vector<ii> adj[moi];

void dfs(int u, int p = -1) {
    ll sum = 0, best1 = 0, best2 = 0;
    for(auto [v, c] : adj[u]) {
        if(v == p) continue;
        dfs(v, u);

        sum += dp[v][0];
        ll val = B - A * c + dp[v][1] - dp[v][0];

        if(val > 0) {
            if(best1 < val) {
                best2 = best1;
                best1 = val;
            }

            else if(best2 < val) best2 = val;
        }
    }

    dp[u][0] = sum + best1 + best2;
    dp[u][1] = sum + best1;
}


void Input() {
    cin >> n >> A >> B;

    for(int i = 1; i < n; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    dfs(1);

    cout << n * B - dp[1][0];
}

main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    if(fopen(task".inp","r")){
        freopen(task".inp","r",stdin);
        freopen(task".out","w",stdout);
    }
    int t = 1;
    //cin >> t;
    while (t --) {
        Input();
    }

    cerr << "Time: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s.\n";
}
