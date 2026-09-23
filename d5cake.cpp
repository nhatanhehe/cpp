#include<bits/stdc++.h>
#define int long long
#define ii pair<int,int>
#define fi first
#define se second
#define task "a"
using namespace std;

const int N = 1e6 + 5, mod = 1e9 + 7;
const int oo = 1e18;
int n;
vector<int> g[N], adj[N];
map<tuple<int,int,int>, int> mp;
int m = 0;
int dp[N][2],state[N],res;

int id(int a, int b, int c)
{
    int x = min({a, b, c});
    int z = max({a, b, c});
    int y = a + b + c - x - z;
    if(!mp.count({x, y, z}))
    {
        mp[{x, y, z}] = ++m;
    }
//    cout << x << ' ' << y << ' ' << z << ' ' << mp[{x, y, z}] << '\n';
    return mp[{x, y, z}];
}

void dfs(int u, int par)
{
    for(int v : adj[u])
    {
        if(v == par) continue;
        dfs(v, u);
    }

    if(state[u]==0){
        state[p]=1;
        state[u]=1;
        res++;
    }

}
main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if(fopen(task ".inp", "r"))
    {
        freopen(task ".inp", "r", stdin);
        freopen(task ".out", "w", stdout);
    }
    cin >> n;
    for(int i = 1; i <= n - 3; i++)
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= n; i++)
    {
        g[i].push_back(i % n + 1);
        g[i % n + 1].push_back(i);
    }
    for(int i = 1; i <= n; i++)
    {
        sort(g[i].begin(), g[i].end(), [&](int x, int y)
        {
            if(x < i) x += n;
            if(y < i) y += n;
            return x <= y;
        });
        // cout << i << ": ";
        // for(int x : g[i]) cout << x << ' ';
        // cout << '\n';
        int cur = 0;
        for(int j = 1; j < g[i].size(); j++)
        {
            int tmp = id(i, g[i][j - 1], g[i][j]);
            if(cur != 0)
            {
                adj[cur].push_back(tmp);
                // adj[tmp].push_back(cur);
                //cout << tmp << ' ' << cur << '\n';
            }
            cur = tmp;
        }
    }
    dfs(1, -1);
    cout << res;
}
