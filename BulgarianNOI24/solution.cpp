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
const ll N=4e5+5;
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
ll n,q,k,u,v,w,in[N],out[N],timer,h[N],p[N][20],dist[N],lvl[N],x,W[N];
vector<ii>g[N];
ii edge[N];
void dfs(int u,int par){
    in[u]=++timer;
    for(int j=1;j<=18;j++) p[u][j]=p[p[u][j-1]][j-1];
    dist[timer]=h[u];
    for(auto [v,w]:g[u]){
        if(v!=par){
            h[v]=h[u]+w;
            lvl[v]=lvl[u]+1;
            p[v][0]=u;
            dfs(v,u);
            timer++;
            dist[timer]=h[u];
        }
    }
    out[u]=timer;
}
int binlift(int u,int tg){
    for(int i=18;i>=0;i--){
        if(lvl[u]-lvl[tg]-1>=(1<<i)) u=p[u][i];
    }
    return u;
}
struct Node{
    ll h,k2h,h2k,h2;
    Node(){
        h = k2h = h2k = h2 = -inf;
    }
};
struct SegmentTree{
    vector<Node>tree;
    vector<ll>lz;
    int n;
    Node merge(Node L,Node R){
        Node res;
        res.h=max(L.h,R.h);
        res.h2=max(L.h2,R.h2);
        res.h2k=max({L.h2k,R.h2k,L.h2+R.h});
        res.k2h=max({L.k2h,R.k2h,L.h+R.h2});
        return res;
    }
    void build(ll a[],int id=1,int l=1,int r=-1){
        if(r==-1) r=n;
        if(l==r){
            tree[id].h=a[l];
            tree[id].h2k=-a[l];
            tree[id].k2h=-a[l];
            tree[id].h2=-2*a[l];
            return;
        }
        int mid=(l+r)>>1;
        build(a,id*2,l,mid);
        build(a, id*2+1, mid+1, r);
        tree[id]=merge(tree[id*2],tree[id*2+1]);
    }
    void init(int _n,ll a[]){
        n=_n;
        tree.resize(n*4+10,Node());
        lz.resize(n*4+10,0);
        build(a);
    }
    void apply(int id,ll val){
        if(tree[id].h!=-inf) tree[id].h+=val;
        if(tree[id].h2k!=-inf) tree[id].h2k-=val;
        if(tree[id].k2h!=-inf) tree[id].k2h-=val;
        if(tree[id].h2!=-inf) tree[id].h2-=2*val;
        lz[id]+=val;
    }
    void push(int id){
        if(lz[id]){
            apply(id*2,lz[id]);
            apply(id*2+1,lz[id]);
        }
        lz[id]=0;
    }
    void up(int u,int v,ll val,int id=1,int l=1,int r=-1){
        if(r==-1) r=n;
        if(l>v||r<u) return;
        if(u<=l&&r<=v){
            apply(id,val);
            return;
        }
        push(id);
        int mid=(l+r)>>1;
        up(u,v,val,id*2,l,mid);
        up(u,v,val,id*2+1,mid+1,r);
        tree[id]=merge(tree[id*2],tree[id*2+1]);
    }
    Node get(int u,int v,int id=1,int l=1,int r=-1){
        if(r==-1) r=n;
        if(l>v||r<u){
            Node dumb=Node();
            return dumb;
        }
        if(u<=l&&r<=v) return tree[id];
        push(id);
        int mid=(l+r)>>1;
        return merge(get(u,v,id*2,l,mid),get(u,v,id*2+1,mid+1,r));
    }
    Node query(int l,int r,vector<ii>A){
        Node res=Node();
        for(auto [u,v]:A){
            u=max(u,l);
            v=min(v,r);
            if(u<=v) res=merge(res,get(u,v));
        }
        return res;
    }
}seg;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>u>>v>>w;
        g[u].pb(ii(v,w));
        g[v].pb(ii(u,w));
        edge[i]=ii(u,v);
        W[i]=w;
    }
    dfs(1,0);
    seg.init(timer,dist);
    cin>>q;
    while(q--){
        int tp;
        cin>>tp;
        if(tp==1){
            cin>>x>>k;
            vector<int>ban(k+1,0);
            int lowban=-1,curr=0;
            ll hx=seg.get(in[x],in[x]).h;
            vector<ii>fob,allowed;
            for(int i=1;i<=k;i++){
                cin>>ban[i];
                int u=ban[i];
                if(in[u]<=in[x]&&out[x]<=out[u]){
                    if(lvl[u]>=lowban){
                        lowban=lvl[u];
                        curr=u;
                    }
                }
                else fob.pb(ii(in[u],out[u]));
            }
            sort(all(fob));
            if(curr==x){
                cout<<0<<'\n';
                continue;
            }
            int L=1,R=timer;
            if (curr!=0){
                int C=binlift(x,curr);
                L=in[C];
                R=out[C];
            }
            int it=L;
            for(auto [l,r]:fob){
                if(it<=l-1){
                    allowed.pb(ii(it,l-1));
                }
                it=max(it,r+1);
            }
            if(it<=R) allowed.pb(ii(it,R));
            ll ans=-inf;
            Node t1=seg.query(in[x],out[x],allowed);
            if(t1.h!=-inf) ans=max(ans,t1.h-hx);
            Node t2=seg.query(L,in[x]-1,allowed);
            if(t2.k2h!=-inf) ans=max(ans,t2.k2h+hx);
            Node t3=seg.query(out[x]+1,R,allowed);
            if(t3.h2k!=-inf) ans=max(ans,t3.h2k+hx);
            cout<<ans<<'\n';
        }
        else{
            int id,w;
            cin>>id>>w;
            auto [u,v]=edge[id];
            if(lvl[u]<lvl[v]) swap(u,v);
            ll delta=w-W[id];
            W[id]=w;
            seg.up(in[u],out[u],delta);
        }
    }
}