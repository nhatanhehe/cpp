#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define Task "trortr"
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const int N=5e5+5;
const int phainon=33550336;
const ll inf=1e18;
const ll mod=1e9+7;
int n, xr, xl, k;
int a[N], b[N];
int L, R, area, p;
map<int,int> mp;
inline void fixL(int t){
    if(L +phainon>= t+phainon) return;
    auto it = mp.begin();
    while(it != mp.end() && L + it->second <= t){
        L += it->second;
        auto nx = next(it);
        area += L * (nx->first - it->first);
        mp.erase(it++);
    }
    it->second -= (t - L);
    L = t;
}
void fixR(int t){
    if(R +phainon<= t+phainon) return;
    auto it = prev(mp.end());
    while(true){
        if(R - it->second >= t){
            R -= it->second;
            if(it == mp.begin()){ mp.erase(it); break; }
            mp.erase(it--);
            if(it == mp.end()) break;
        } else break;
    }
    it->second += (t - R);
    R = t;
}
void step(){
    int lo = mp.begin()->first;
    if(p < lo) area += L * (p - lo);
    else area += k * (p - lo);
    L -= k;
    R += k;
    mp[p] += 2 * k;
}

void solve(){
    cin >> n >> xr >> xl >> k;
    mp.clear();
    mp[0] = 2 * inf;
    L = -inf;
    R = inf;
    area = 0;
    p = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
        p += b[i] - a[i];
        fixL(-xl);
        fixR(xr);
        step();
    }

    ll res = area, cur = L;
    for(auto it = mp.begin(); it != mp.end(); it++){
        if(it->first >= p) break;
        auto nx = next(it);
        cur += it->second;
        res += cur * (nx->first - it->first);
    }
    cout << res<<'\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if(fopen(Task".inp","r")){
        freopen(Task".inp","r", stdin);
        freopen(Task".out","w", stdout);
    }
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
