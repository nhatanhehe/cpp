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
const ll N=2e5+5;
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
int n,m,u,v,w,we[N],timer,in[N],out[N],h[N],p[N][20],root[N],cur;
vector<ii>g[N];
struct edge{
    int u,v,w;
}e[N];
vector<int>cp;
struct Node{
    int l,r,val;
    Node(){
        l = r = val = 0;
    }
}tree[N*30];
void build(int id=1,int l=1,int r=n){
    if(l==r){
        tree[id].val=0;
        return;
    }
    int mid=(l+r)>>1;
    tree[id].l=++cur;
    tree[id].r=++cur;
    build(tree[id].l,l,mid);
    build(tree[id].r,mid+1,r);
    tree[id].val=tree[tree[id].l].val+tree[tree[id].r].val;
}
void up(int pos,int k,int id,int l=1,int r=n){
    if(l==r){
        tree[id].val+=k;
        return;
    }
    int mid=(l+r)>>1;
    if(pos<=mid){
        tree[++cur]=tree[tree[id].l];
        tree[id].l=cur;
        up(pos,k,tree[id].l,l,mid);
    }
    else{
        tree[++cur]=tree[tree[id].r];
        tree[id].r=cur;
        up(pos,k,tree[id].r,mid+1,r);
    }
    tree[id].val=tree[tree[id].l].val+tree[tree[id].r].val;
}
int get(int idu,int idv,int idlca,int u,int v,int l=1,int r=n){
    if(l>v||r<u) return 0;
    if(u<=l&&r<=v) return tree[idu].val+tree[idv].val-2*tree[idlca].val;
    int mid=(l+r)>>1;
    return get(tree[idu].l,tree[idv].l,tree[idlca].l,u,v,l,mid)+get(tree[idu].r,tree[idv].r,tree[idlca].r,u,v,mid+1,r);
}
void dfs(int u,int par){
    in[u]=++timer;
    root[u]=++cur;
    tree[root[u]]=tree[root[par]];
    if(u!=1){
        int pos=upper_bound(all(cp),we[u])-cp.begin();
        up(pos,1,root[u]);
    }
    for(auto [v,w]:g[u]){
        if(v!=par){
            h[v]=h[u]+1;
            p[v][0]=u;
            we[v]=w;
            dfs(v,u);
        }
    }
    out[u]=timer;
}
void init_lca(){
    for(int j=1;j<=18;j++){
        for(int i=1;i<=n;i++){
            p[i][j]=p[p[i][j-1]][j-1];
        }
    }
}
int lca(int u,int v){
    if(h[u]<h[v]) swap(u,v);
    for(int i=18;i>=0;i--){
        if(h[u]-h[v]>=(1<<i)) u=p[u][i];
    }
    if(u==v) return u;
    for(int i=18;i>=0;i--){
        if(p[u][i]!=p[v][i]){
            u=p[u][i];
            v=p[v][i];
        }
    }
    return p[u][0];
}
struct QueryT {
    int id, k, c, v, nd, w;
    bool operator<(const QueryT& o) const {
        return c < o.c;
    }
};
vector<QueryT> qT;
int ans_out[N];
int bit[N];
void update(int i, int val) {
    for(; i<=n; i+=i&-i) bit[i]+=val;
}
int query(int i) {
    int res=0;
    for(; i>0; i-=i&-i) res+=bit[i];
    return res;
}
struct EdgeInfo {
    int w, in_pos;
    bool operator<(const EdgeInfo& o) const {
        return w < o.w;
    }
};
vector<EdgeInfo> edge_info;
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cin>>n>>m;
    for(int i=1;i<n;i++){
        cin>>u>>v>>w;
        e[i]={u,v,w};
        g[u].pb({v,w});
        g[v].pb({u,w});
        cp.pb(w);
    }
    sort(all(cp));
    cp.erase(unique(all(cp)),cp.end());
    root[0]=cur=1;
    build();
    dfs(1,0);
    init_lca();
    for(int i=2;i<=n;i++) edge_info.pb({we[i], in[i]});
    sort(all(edge_info));
    for(int i=1;i<=m;i++){
        char tp;
        cin>>tp;
        if(tp=='P'){
            int a,b,c;
            cin>>a>>b>>c;
            int acs=lca(a,b);
            int pos=upper_bound(all(cp),c)-cp.begin();
            ans_out[i]=get(root[a],root[b],root[acs],1,pos);
        }
        else{
            int k,c;
            cin>>k>>c;
            auto [u,v,w]=e[k];
            int nd=v;
            if(h[u]>h[v]) swap(u,v);
            qT.pb({i,k,c,v,nd,w});
        }
    }
    sort(all(qT));
    int ptr = 0;
    for(auto q : qT){
        while(ptr < (int)edge_info.size() && edge_info[ptr].w <= q.c){
            update(edge_info[ptr].in_pos, 1);
            ptr++;
        }
        int cntv = query(out[q.v]) - query(in[q.v]);
        int cnt = query(n) - query(1);
        if(q.v == q.nd) ans_out[q.id] = cntv;
        else ans_out[q.id] = cnt - cntv - (q.w <= q.c);
    }
    for(int i=1;i<=m;i++){
        cout<<ans_out[i]<<'\n';
    }
}
