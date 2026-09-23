#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ii pair<int, int>
#define iii pair<int, ii>
#define iiii pair<ii, ii>
#define fi first
#define se second
const int N = 1e5 + 5;
iii edge[N];
int n, par[N];
ii x[N], y[N], z[N];
vector<iii> ds;
bool cmp(ii a, ii b){
    return a.fi < b.fi;
}
int acs(int u){
    if (par[u] == u) return u;
    else return par[u] = acs(par[u]);
}
void join(int u, int v){
    int x = acs(u);
    int y = acs(v);
    if (x != y) par[x] = y;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n;i++){
        cin >> x[i].fi >> y[i].fi;
        x[i].se = i;
        y[i].se = i;
        par[i] = i;
    }
    sort(x + 1, x + 1 + n, cmp);
    for (int i = 2; i <= n;i++){
        ds.push_back({abs(x[i].fi - x[i - 1].fi),{x[i - 1].se, x[i].se}});
    }
    sort(y + 1, y + 1 + n, cmp);
    for (int i = 2; i <= n;i++){
        ds.push_back({abs(y[i].fi - y[i - 1].fi),{y[i - 1].se, y[i].se}});
    }
    sort(ds.begin(), ds.end());
    int ans = 0;
    for (auto v : ds){
        if (acs(v.se.fi) != acs(v.se.se)){
            join(v.se.fi,v.se.se);
            ans+= v.fi;
        }
    }
    cout << ans;
}

