#include <bits/stdc++.h>
#define task "fakernum"
#define int long long
#define ll long long
#define ld long double
#define ii pair<int, int>
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define mems(x, y) memset(x, y, sizeof(x));
using namespace std;
const int mod = 1e9 + 7, moi = 1e5 + 9;
const ll INF = 1e18;
const ld EFS = 1e-12;
const int dx[] = { 1, -1, 0, 0};
const int dy[] = { 0, 0, 1, -1};


unordered_map<int, int> mp;

struct segment_tree {
    vector<int> t;
    int n;

    void init(int _n) {
        n = _n;
        t.resize(n + 9);
    }

    void update(int pos, int c, int id, int l, int r) {
        if(l == r) {
            t[id] += c;
            return;
        }

        int mid = (l + r) / 2;
        if(pos <= mid) update(pos, c, id * 2, l, mid);
        else update(pos, c, id * 2 + 1, mid + 1, r);

        t[id] = t[id * 2] + t[id * 2 + 1];
    }

    int get(int u, int v, int id, int l, int r) {
        if(u > r || v < l) return 0;
        if(u <= l && r <= v) return t[id];

        int mid = (l + r) / 2;
        return (get(u, v, id * 2, l, mid) + get(u, v, id * 2 + 1, mid + 1, r));
    }

    void update(int pos, int c) {
        update(pos, c, 1, 1, n);
    }

    int get(int u, int v) {
        return get(u, v, 1, 1, n);
    }
};

int n, q, par[moi], sz[moi], d[moi], val[moi], a[moi], tin[moi], tout[moi];
int save[moi], ID[moi], pos[moi], ID_HEAD[moi], cnt_chuoi = 1, cnt_pos = 1, cnt = 0;
ll dp[moi];
vector<int> adj[moi];

void dfs(int u, int p = -1) {
    tin[u] = ++cnt;
    save[cnt] = u;
    sz[u] = 1;
    for(int v : adj[u]) {
        if(v == p) continue;
        d[v] = d[u] + 1;
        par[v] = u;
        dfs(v, u);
        sz[u] += sz[v];
    }
    tout[u] = cnt;
}

void hld(int u, int p = -1) {
    if(!ID_HEAD[cnt_chuoi]) {
        ID_HEAD[cnt_chuoi] = u;
    }

    ID[u] = cnt_chuoi;
    pos[u] = cnt_pos;
    cnt_pos ++;

    int nx = 0;
    for(int v : adj[u]) {
        if(v == p) continue;
        if(nx == 0 || sz[v] > sz[nx]) nx = v;
    }

    if(nx) hld(nx, u);

    for(int v : adj[u]) {
        if(v == p || v == nx) continue;
        cnt_chuoi++;
        hld(v, u);
    }
}

int lca(int u, int v) {
    while(ID[u] != ID[v]) {
        if(ID[u] > ID[v]) {
            u = par[ID_HEAD[ID[u]]];
        }
        else v = par[ID_HEAD[ID[v]]];
    }

    if(d[u] < d[v]) return u;
    return v;
}

segment_tree th, te;

int query(int u, int v) {
    int l = lca(u, v);
    int ans = 0;

    while(ID[u] != ID[l]) {
        ans += th.get(pos[ID_HEAD[ID[u]]], pos[u]);
        u = par[ID_HEAD[ID[u]]];
    }

    while(ID[v] != ID[l]) {
        ans += th.get(pos[ID_HEAD[ID[v]]], pos[v]);
        v = par[ID_HEAD[ID[v]]];
    }

    if(d[u] < d[v]) {
        ans += th.get(pos[u], pos[v]);
    }
    else ans += th.get(pos[v], pos[u]);

    return ans;
}

bool check(ll x) {
    string s = to_string(x);
    int n = s.size() - 1;
    int ans = 0;

    for(int i = 0; i <= n; i++) {

        int l = i, r = i;
        while(l >= 0 && r <= n && s[l] == s[r]) {
            ans ++;
            l --;
            r ++;
        }

        l = i, r = i + 1;
        while(l >= 0 && r <= n && s[l] == s[r]) {
            ans ++;
            l --;
            r ++;
        }
    }

    n++;
    int sz = n * (n + 1) / 2;

    ld tile = (ld) ans / sz;
    return (tile > 0.5);
}

void cal(int i, int N, ll val, int d3, int d6) {
    if(i > N) {
        if(check(val)) {
            mp[val] = 1;
        }
        return;
    }

    if(d3 < N / 2) cal(i + 1, N, val * 10 + 3, d3 + 1, d6);
    if(d6 < N / 2) cal(i + 1, N, val * 10 + 6, d3, d6 + 1);
}

void pre() {
    for(int i = 2; i < 16; i += 2) {
        cal(1, i, 0, 0, 0);
    }
}

void dfs2_update(int u, int p, int x) {
    while(u != p) {
        dp[u] += x;
        u = par[u];
    }
}

int dfs2_get(int u, int p) {
    int ans = 0;
    while(u != p) {
        if(mp.find(dp[u]) != mp.end()) ans++;
        u = par[u];
    }

    return ans;
}

void sub1() {
    for(int i = 1; i <= n; i++) {
        dp[i] = a[i];
    }

    while(q--) {
        int type;

        cin >> type;

        if(type == 1) {
            int u, v, c;
            cin >> u >> v >> c;

            int l = lca(u, v);
            dfs2_update(u, l, c);
            dfs2_update(v, l, c);

            dp[l] += c;
        }

        if(type == 2) {
            int u, v;
            cin >> u >> v;

            int res = 0;
            int l = lca(u, v);

            res += dfs2_get(u, l) + dfs2_get(v, l);
            if(mp.find(dp[l]) != mp.end()) res++;

            cout << res << '\n';
        }

        if(type == 3) {
            int u;
            cin >> u;
            int res = 0;

            for(int i = tin[u]; i <= tout[u]; i++) {

                if(mp.find(dp[save[i]]) != mp.end()) res++;
            }

            cout << res << '\n';
        }
    }
}

void sub2() {
    th.init(n);
    te.init(n);

    for(int i = 1; i <= n; i++) {
        th.update(pos[i], mp.find(a[i]) != mp.end());
        te.update(tin[i], mp.find(a[i]) != mp.end());
    }

    while(q--) {
         int type;

        cin >> type;

        if(type == 2) {
            int u, v;
            cin >> u >> v;

            cout << query(u, v) << '\n';
        }

        if(type == 3) {
            int u;
            cin >> u;

            cout << te.get(tin[u], tout[u]) << '\n';
        }
    }
}

void Input() {
    cin >> n >> q;

    for(int i = 1; i <= n; i++) cin >> a[i];

    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1);
    hld(1);


    if(n <= 1000 && q <= 5000) {
        sub1();
        return;
    }

    sub2();
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
    pre();
    while (t --) {
        Input();
    }

    cerr << "Time: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s.\n";
}
