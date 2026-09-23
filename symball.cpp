#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define debug(x) cout<< #x << " = "<< x <<'\n'
#define Task "a"
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf=1e18;
const ll N=1e6+5;
const ll mod=998244353;
const ll base=311;
const ll phainon=33550336;
#define On(mask,i) (mask|(1LL<<i))
#define Off(mask,i) (mask&~(1LL<<i))
inline ll add(ll a,ll b){
    ll res=a+b;
    if(res>=mod) res-=mod;
    return res;
}
ll sub(ll a,ll b){
    return ((a-b)%mod+mod)%mod;
}
inline ll mul(ll a,ll b){
    ll res=a*b;
    if(res>=mod) res%=mod;
    return res;
}
int n,q,a[N],ans[N];
vector<int>cp;
vector<ii>Q[N];
int last[N];
ll bit[N];
void up(int i,ll k){
    for(;i<=n;i+=i&-i){
        bit[i]+=k;
    }
}
ll get(int i){
    ll res=0;
    for(;i;i-=i&-i){
        res+=bit[i];
    }
    return res;
}
ll query(int l,int r){
    return get(r)-get(l-1);
}
ll exp(ll a, ll e){
    a %= mod;
    ll r = 1;
    while(e){
        if(e & 1) r = (r * a) % mod;
        a = (a * a) % mod;
        e >>= 1;
    }
    return r;
}
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        cp.pb(a[i]);
    }
    sort(all(cp));
    cp.erase(unique(all(cp)),cp.end());
    for(int i=1;i<=n;i++){
        a[i]=upper_bound(all(cp),a[i])-cp.begin();
    }
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        Q[r].pb(ii(l,i));
    }
    for(int i=1;i<=n;i++){
        if(last[a[i]]){
            up(last[a[i]],-1);
        }
        last[a[i]]=i;
        up(i,1);
        for(auto [l,id]:Q[i]){
            ll distinct=query(l,i);
            ll len=i-l+1;
            ans[id]=sub(mul(1+distinct,exp(2,len-distinct)),1);
        }
    }
    for(int i=1;i<=q;i++){
        cout<<ans[i]<<'\n';
    }
}
