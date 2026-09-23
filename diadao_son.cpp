#include <bits/stdc++.h>
#define task "a"
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

struct BIT {
    vector<int> t;
    int n;

    void init(int _n) {
        n = _n;
        t.resize(n + 9);
    }

    void update(int u, int v) {
        for(; u <= n; u += u&-u) {
            t[u] += v;
        }
    }

    int get(int u) {
        ll ans = 0;

        for(; u > 0; u -= u&-u) {
            ans += t[u];
        }

        return ans;
    }

    void update(int l, int r, int v) {
        update(l, v);
        update(r + 1, -v);
    }
};

int n, m, cnt = 0, tin[moi], tout[moi], h[moi], up[moi][20];
vector<int> adj[moi];
BIT t;

ll lca(int u, int v) {
    if(h[u] < h[v]) swap(u, v);

    int k = h[u] - h[v];
    for(int j = 0; (1 << j) <= k; j++) {
        if(k >> j & 1) u = up[u][j];
    }

    if(u == v) return u;

    for(int j = __lg(h[u]); j >= 0; j--) {
        if(up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }

    return up[u][0];
}

ll dist(int u, int v) {
    int l = lca(u, v);

    return h[u] + h[v] - h[l];
}

ll anc_k(int u, int k) {
    for(int j = 0; (1 << j) <= k; j++) {
        if(k >> j & 1) u = up[u][j];
    }
    return u;
}

void dfs(int u, int p) {
    tin[u] = ++cnt;

    for(int v : adj[u]) {
        if(v == p) continue;

        h[v] = h[u] + 1;
        up[v][0] = u;
        for(int j = 1; j < 20; j ++) {
            up[v][j] = up[up[v][j - 1]][j - 1];
        }

        dfs(v, u);
    }

    tout[u] = cnt;
}

bool ok = true;
int vis[moi];
vector<int> g[moi];
vector<ii> vec;

void dfs2(int u) {
    vis[u] = 1;

    for(int v : g[u]) {

        if(!vis[v]) dfs2(v);

        if(vis[v] == 1) {
            ok = false;
            return;
        }
    }

    vis[u] = 2;
}

void Input() {
    cin >> n >> m;

    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);
    t.init(n);


    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
        vec.push_back({u, v});
    }

    for(int i = 1; i <= n; i++) {
        if(!vis[i]) dfs2(i);
    }

    if(!ok) {
        for(int i = 1; i <= n; i++) cout << 0 << '\n';
        return;
    }


    for(auto [u, v] : vec) {

        if(tin[u] <= tin[v] && tout[v] <= tout[u]) {

            ll dist1 = h[v] - h[u] - 1;
            v = anc_k(v, dist1);

            t.update(1, n, 1);
            t.update(tin[v], tout[v], -1);
        }

        else {

            t.update(tin[u], tout[u], 1);
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << (t.get(tin[i]) <= 0) << '\n';
    }
}

int main(){
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

