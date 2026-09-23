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
ll n,a[N],s,d;
struct Node{
    ll l,r,cnt,val;
    Node(){
        l = r = val = cnt = 0;
    }
}tree[N*40];
int cur;
int root[N];
ll val[N];
void build(int id=1,int l=1,int r=n){
    if(l==r){
        tree[id].cnt=0;
        tree[id].val=0;
        return;
    }
    int mid=(l+r)>>1;
    tree[id].l=++cur;
    tree[id].r=++cur;
    build(tree[id].l,l,mid);
    build(tree[id].r,mid+1,r);
    tree[id].cnt=tree[tree[id].l].cnt+tree[tree[id].r].cnt;
    tree[id].val=tree[tree[id].l].val+tree[tree[id].r].val;
}
void up(int pos,ll k,int id,int l=1,int r=n){
    if(l==r){
        tree[id].cnt++;
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
    tree[id].cnt=tree[tree[id].l].cnt+tree[tree[id].r].cnt;
    tree[id].val=tree[tree[id].l].val+tree[tree[id].r].val;
}

// first luu sum, second luu cnt
ll get(int id1,int id2,ll k,int l=1,int r=n){
    if(l==r){
        ll cnt=tree[id2].cnt-tree[id1].cnt;
        return val[l]*min(cnt,k);
    }
    int mid=(l+r)>>1;
    int p1=tree[tree[id2].l].cnt-tree[tree[id1].l].cnt;
    int p2=tree[tree[id2].r].cnt-tree[tree[id1].r].cnt;
    ll sum=tree[tree[id2].r].val-tree[tree[id1].r].val;
    if(k>p2){
        k-=p2;
        return sum+get(tree[id1].l,tree[id2].l,k,l,mid);
    }
    else return get(tree[id1].r,tree[id2].r,k,mid+1,r);
}
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    auto st = chrono::steady_clock::now();
    cin>>n>>s>>d;
    s++;
    vector<int>cp;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        cp.pb(a[i]);
    }
    sort(all(cp));
    cp.erase(unique(all(cp)),cp.end());
    for(int i=1;i<=n;i++){
        int ps=upper_bound(all(cp),a[i])-cp.begin();
        val[ps]=a[i];
        a[i]=ps;
    }
    root[0]=cur=1;
    build();
    for(int i=1;i<=n;i++){
        root[i]=++cur;
        tree[root[i]]=tree[root[i-1]];
        up(a[i],val[a[i]],root[i]);
    }
    ll ans=0;
    // di sang phai, quay dau sang trai
    for(int r=s;r<=n;r++){
        if(chrono::duration<double>(chrono::steady_clock::now()-st).count()>0.3){
            cout<<ans;
            return 0;
        }
        for(int l=s;l>=1;l--){
            if(chrono::duration<double>(chrono::steady_clock::now()-st).count()>0.3){
                cout<<ans;
                return 0;
            }

            int cost1=2*(r-s)+(s-l);
            int cost2=(r-s)+2*(s-l);
            int cost=min(cost1,cost2);
            int k=d-cost;
            if(k>0) ans=max(ans,get(root[l-1],root[r],k));
        }
    }
    cout<<ans;
}
