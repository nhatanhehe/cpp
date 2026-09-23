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
const ll N=3e5+5;
const ll mod=1e9+7;
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
int n,u,v,in[N],out[N],t,root,timer;
vector<int>g[N];
vector<int>query[N];
struct BIT{
    int bit[N];
    void update(int x){
        while(x<=n){
            bit[x]++;
            x+=x&-x;
        }
    }
    int get(int x){
        int res=0;
        while(x){
            res+=bit[x];
            x-=x&-x;
        }
        return res;
    }
}bit;
void dfs(int u,int p){
    in[u]=++timer;
    for(int v:g[u]){
        if(v!=p) dfs(v,u);
    }
    out[u]=timer;
}
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cin>>t>>n>>root;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(root,-1);
    for(int i=1;i<=n;i++){
        if(i>1) query[i-1].pb(i);
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        bit.update(in[i]);
        for(int v:query[i]){
            ans+=bit.get(out[v])-bit.get(in[v]-1);
        }
    }
    cout<<ans;
}
