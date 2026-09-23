#include<bits/stdc++.h>
using namespace std;
#define task "a"
#define ll long long
#define int long long
#define pb push_back
#define ii pair<ll, ll>
#define fi first
#define se second
#define all(x) x.begin(),x.end()
const long N = 1e5 + 7;
const int mod=998244353;
inline int add(int a,int b){
    if(a>=mod) a%=mod;
    if(b>=mod) b%=mod;
    return (a+b)%mod;
}
inline int mul(int a,int b){
    return (a%mod)*(b%mod)%mod;
}
inline int sub(int a,int b){
    ll res=(a-b)%mod;
    if(res<=mod) res+=mod;
    return res%mod;
}
int n,q,m[N],u,v;
vector<int>g[N];
vector<int>Q[N];
namespace sub1{
    int deg[N];
    void solve(){
        for(int i=1;i<=q;i++){
            fill(deg+1,deg+n+1,0);
            queue<int>pq;
            for(int u:Q[i]){
                deg[u]=1;
                pq.push(u);
            }
            int cnt=0;
            while(pq.size()){
                queue<int>nxt;
                while(pq.size()){
                    int u=pq.front(); pq.pop();
                    cnt++;
                    for(int v:g[u]){
                        deg[v]++;
                        if(deg[v]==1){
                            nxt.push(v);
                        }
                    }
                }
                while(nxt.size()){
                    int u=nxt.front(); nxt.pop();
                    if(deg[u]==1) pq.push(u);
                }
            }
            cout<<cnt<<'\n';
        }
    }
}
int h[N],p[N][20],sz[N];
void dfs(int u,int par){
    sz[u]=1;
    for(int v:g[u]){
        if(v!=par){
            h[v]=h[u]+1;
            p[v][0]=u;
            dfs(v,u);
            sz[u]+=sz[v];
        }
    }
}
int lca(int u,int v){
    if(h[u]<h[v]) swap(u,v);
    for(int i=19;i>=0;i--){
        if(h[u]-h[v]>=(1<<i)) u=p[u][i];
    }
    if(u==v) return u;
    for(int i=19;i>=0;i--){
        if(p[u][i]!=p[v][i]){
            u=p[u][i];
            v=p[v][i];
        }
    }
    return p[u][0];
}
namespace sub3{
    int binlift(int u,int dist){
        for(int i=0;i<=19;i++){
            if((dist>>i)&1) u=p[u][i];
        }
        return u;
    }
    void solve(){
        for(int i=1;i<=q;i++){
            if(m[i]==1) cout<<n<<'\n';
            else{
                int u=Q[i][0];
                int v=Q[i][1];
                if(h[u]>h[v]) swap(u,v);
                int lc=lca(u,v);
                if(lc==u){
                    int dist=h[v]-h[u];
                    if(dist&1) cout<<n<<'\n';
                    else{
                        int dist2=dist/2;
                        int u2=binlift(v,dist2);
                        int u3=binlift(v,dist2-1);
                        //cout<<dist2<<" "<<u2<<'\n';
                        cout<<n-(sz[u2]-sz[u3])<<'\n';
                    }
                }
                else{
                    int distu=h[u]-h[lc];
                    int distv=h[v]-h[lc];
                    if(distu==distv){
                        int u2=binlift(u,distu-1);
                        int v2=binlift(v,distv-1);
                        cout<<sz[u2]+sz[v2]<<'\n';
                    }
                    else{
                        int dist=distu+distv;
                        if(dist&1) cout<<n<<'\n';
                        else{
                            int dist2=dist/2-1;
                            int v2=binlift(v,dist2);
                            int v3=binlift(v,dist2+1);
                            cout<<n-(sz[v3]-sz[v2])<<'\n';
                        }
                    }
                }
            }
        }
    }
}
int cnt=0;
main(){
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    freopen(task".INP", "r", stdin);
    freopen(task".OUT", "w", stdout);
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(1,-1);
    for(int j=1;j<=19;j++){
        for(int i=1;i<=n;i++){
            p[i][j]=p[p[i][j-1]][j-1];
        }
    }
    cin>>q;
    int mx=0;
    for(int i=1;i<=q;i++){
        cin>>m[i];
        mx=max(mx,m[i]);
        for(int j=1;j<=m[i];j++){
            int x;
            cin>>x;
            Q[i].pb(x);
        }
    }
    if(n<=1e3&&q<=1e3) sub1::solve();
    else sub3::solve();
}

