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
const ll N=1e5+5;
const ll MAX_NODES=N*40;

ll n,m,q,u,v;
vector<ii> g[N];
vector<ll> stations[N],cp;
ll val[N],tram[N],h[N];
ll p[N][19];

struct Node{
    ll cnt,sum;
    ll l,r;
}tree[MAX_NODES];

ll cur,root[N];

void up(ll old_id,ll &new_id,ll l,ll r,ll pos,ll k){
    new_id=++cur;
    tree[new_id]=tree[old_id];
    tree[new_id].cnt++;
    tree[new_id].sum+=k;
    if(l==r) return;
    ll mid=(l+r)>>1;
    if(pos<=mid) up(tree[old_id].l,tree[new_id].l,l,mid,pos,k);
    else up(tree[old_id].r,tree[new_id].r,mid+1,r,pos,k);
}

ll get(ll u,ll v,ll a,ll l,ll r,ll k){
    ll tot=tree[u].cnt+tree[v].cnt-2*tree[a].cnt;
    if(tot==0||k<=0) return 0;
    if(l==r) return min(tot,k/val[l]);
    ll mid=(l+r)>>1;
    ll suml=tree[tree[u].l].sum+tree[tree[v].l].sum-2*tree[tree[a].l].sum;
    ll cntl=tree[tree[u].l].cnt+tree[tree[v].l].cnt-2*tree[tree[a].l].cnt;
    if(k>=suml) return cntl+get(tree[u].r,tree[v].r,tree[a].r,mid+1,r,k-suml);
    return get(tree[u].l,tree[v].l,tree[a].l,l,mid,k);
}

void dfs(ll u,ll par){
    for(auto x:g[u]){
        ll v=x.fi,id=x.se;
        if(v==par) continue;
        h[v]=h[u]+1;
        p[v][0]=u;
        tram[v]=tram[u]+stations[id].size();
        ll cur_root=root[u];
        for(ll c:stations[id]){
            ll pos=lower_bound(all(cp),c)-cp.begin()+1;
            ll new_root=0;
            up(cur_root,new_root,1,cp.size(),pos,c);
            cur_root=new_root;
        }
        root[v]=cur_root;
        dfs(v,u);
    }
}

ll lca(ll u,ll v){
    if(h[u]<h[v]) swap(u,v);
    for(ll i=18;i>=0;i--)
        if(h[u]-h[v]>=(1LL<<i))
            u=p[u][i];
    if(u==v) return u;
    for(ll i=18;i>=0;i--)
        if(p[u][i]!=p[v][i]){
            u=p[u][i];
            v=p[v][i];
        }
    return p[u][0];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if(fopen(Task".inp","r")){
        freopen(Task".inp","r",stdin);
        freopen(Task".out","w",stdout);
    }

    cin>>n>>m>>q;
    for(ll i=1;i<n;i++){
        cin>>u>>v;
        g[u].pb({v,i});
        g[v].pb({u,i});
    }

    for(ll i=1;i<=m;i++){
        ll id,c;
        cin>>id>>c;
        stations[id].pb(c);
        cp.pb(c);
    }

    sort(all(cp));
    cp.erase(unique(all(cp)),cp.end());
    for(ll i=0;i<cp.size();i++) val[i+1]=cp[i];

    dfs(1,0);

    for(ll j=1;j<=18;j++)
        for(ll i=1;i<=n;i++)
            p[i][j]=p[p[i][j-1]][j-1];

    while(q--){
        ll s,t,x,y;
        cin>>s>>t>>x>>y;
        ll w=lca(s,t);
        ll len=tram[s]+tram[t]-2*tram[w];
        ll silver=0;
        if(!cp.empty()) silver=get(root[s],root[t],root[w],1,cp.size(),y);
        ll need=len-silver;
        if(x>=need) cout<<x-need<<'\n';
        else cout<<-1<<'\n';
    }
}
