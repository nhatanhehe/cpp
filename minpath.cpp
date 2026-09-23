#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define debug(x) cout<< #x << " = "<< x <<'\n'
#define Task "MINPATH"
#define ii pair<ll,ll>
#define iii pair<ii,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf=1e18;
const ll N=1e4+5;
const ll mod=1e9+7;
const ll base=311;
const ll phainon=33550336;
#define On(mask,i) (mask||(1LL<<i))
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
ll n,m,p,l,k,u,w,v,dist[N][15][15];
vector<ii>g[N];
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cin>>n>>m>>p>>l>>k;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
        g[u].pb({v,w});
        g[v].pb({u,w});
    }
    memset(dist,0x3f,sizeof dist);
    priority_queue<iii,vector<iii>,greater<iii>>pq;
    dist[1][0][0]=0;
    pq.push({ii(0,1),ii(0,0)});
    while(pq.size()){
        auto [x1,x2]=pq.top(); pq.pop();
        auto [cost,u]=x1;
        auto [mg,portal]=x2;
        if(u==n){
            return cout<<cost,0;
        }
        if(cost>dist[u][mg][portal]) continue;
        for(auto [v,w]:g[u]){
            if(portal<k && l>0){
                if(dist[v][l-1][portal+1]>dist[u][mg][portal]+p){
                    dist[v][l-1][portal+1]=dist[u][mg][portal]+p;
                    pq.push({ii(dist[v][l-1][portal+1],v),ii(l-1,portal+1)});
                }
            }
            if(mg){
                if(dist[v][mg-1][portal]>dist[u][mg][portal]){
                    dist[v][mg-1][portal]=dist[u][mg][portal];
                    pq.push({ii(dist[v][mg-1][portal],v),ii(mg-1,portal)});
                }
            }
            else{
                if(dist[v][mg][portal]>dist[u][mg][portal]+w){
                    dist[v][mg][portal]=dist[u][mg][portal]+w;
                    pq.push({ii(dist[v][mg][portal],v),ii(mg,portal)});
                }
            }
        }
    }
}