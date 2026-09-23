#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define debug(x) cout<< #x << " = "<< x <<'\n'
#define Task "a"
#define ii pair<ll,ll>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf=1e18;
const ll N=2e5+5;
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
int fgcd(unsigned  int u , unsigned  int v){
    int shift,uz,vz;
    if(u==0)  return v;
    if(v==0)  return u;
    uz=__builtin_ctz(u);
    vz=__builtin_ctz(v);
    shift=uz>vz? vz:uz;
    u>>=uz;
    do{
        v>>= vz ;
        int diff=v;
        diff-=u;
        vz=__builtin_ctz(diff);
        if(diff==0) break;
        if(v<u) u=v;
        v=abs(diff);
  }while(1);
  return u<<shift ;
}
ll n,q,k,a[N],l,r,f[N][20],L[N],cur,root[N],ans[N];
ll getg(int l,int r){
    int k=31-__builtin_clz(r-l+1);
    return fgcd(f[l][k],f[r-(1<<k)+1][k]);
}
struct Node{
    ll l,r,cnt,val;
    Node(){
        l = r = val = cnt = 0;
    }
}tree[N*40];
void build(int id=1,int l=1,int r=n){
    if(l==r){
        tree[id].val=0;
        tree[id].cnt=0;
        return;
    }
    int mid=(l+r)>>1;
    tree[id].l=++cur;
    tree[id].r=++cur;
    build(tree[id].l,l,mid);
    build(tree[id].r,mid+1,r);
    tree[id].val=tree[tree[id].l].val+tree[tree[id].r].val;
    tree[id].cnt=tree[tree[id].l].cnt+tree[tree[id].r].cnt;
}
void up(int pos,ll k,int id,int l=1,int r=n){
    if(l==r){
        tree[id].val+=k;
        tree[id].cnt++;
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
    tree[id].cnt=tree[tree[id].l].cnt+tree[tree[id].r].cnt;
}

// first luu sum, second luu cnt
ii get(int id1,int id2,int u,int v,int l=1,int r=n){
    if(l>v||r<u) return ii(0,0);
    if(u<=l&&r<=v) return ii(tree[id2].val-tree[id1].val,tree[id2].cnt-tree[id1].cnt);
    int mid=(l+r)>>1;
    ii p1=get(tree[id1].l,tree[id2].l,u,v,l,mid);
    ii p2=get(tree[id1].r,tree[id2].r,u,v,mid+1,r);
    return ii(p1.fi+p2.fi,p1.se+p2.se);
}
vector<ii>g[N];
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cin>>n>>q>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        f[i][0]=a[i];
    }
    for(int j=1;j<=18;j++){
        for(int i=1;i+(1<<j)-1<=n;i++){
            f[i][j]=fgcd(f[i][j-1],f[i+(1<<(j-1))][j-1]);
        }
    }
    //cout<<__gcd(f[3][0],f[3+(1<<0)][0])<<'\n';
    for(int i=1;i<=n;i++){
        int l=1,r=i,res=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(getg(mid,i)<=k){
                l=mid+1;
                res=mid;
            }
            else r=mid-1;
        }
        L[i]=res;
        //cout<<L[i]<<" ";
    }
    root[0]=cur=1;
    build();
    for(int i=1;i<=q;i++){
        cin>>l>>r;
        g[r].pb(ii(l,i));
    }
    for(int i=1;i<=n;i++){
        root[i]=++cur;
        tree[root[i]]=tree[root[i-1]];
        if(L[i]){
            up(L[i],L[i],root[i]);
        }
        for(ii x:g[i]){
            int l=x.fi;
            int id=x.se;
            ii res=get(root[l-1],root[i],l,i);
            ll sum=res.fi;
            ll cnt=res.se;
            ans[id]=sum-cnt*l+cnt;
        }
    }
    for(int i=1;i<=q;i++){
        cout<<ans[i]<<'\n';
    }
}
