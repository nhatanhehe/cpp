#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define Task "binque"
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf=1e18;
const ll N=2e5+5;
const ll mod=1e9+7;
const ll base=311;
#define On(mask,i) (mask|(1LL<<i))
#define Off(mask,i) (mask^(1LL<<i))

inline ll add(ll a,ll b){
    a+=b;
    if(a>=mod) a-=mod;
    return a;
}
inline ll sub(ll a,ll b){
    a-=b;
    if(a<0) a+=mod;
    return a;
}
inline ll mul(ll a,ll b){
    return (a*b)%mod;
}

string s;
int tp,u,v,x,q;
int pre[N],sum[N],tree[N<<2],n,lz[N<<2],pw[N];

void fix(int id,int l,int r,int k){
    if(k==1) tree[id]=sub(sum[r],sum[l-1]);
    else tree[id]=0;
    lz[id]=k;
}

void push(int id,int l,int r){
    if(lz[id]==-1) return;
    int mid=(l+r)>>1;
    fix(id<<1,l,mid,lz[id]);
    fix(id<<1|1,mid+1,r,lz[id]);
    lz[id]=-1;
}

void up(int u,int v,int x,int id=1,int l=1,int r=n){
    if(l>v||r<u) return;
    if(u<=l&&r<=v){
        fix(id,l,r,x);
        return;
    }
    push(id,l,r);
    int mid=(l+r)>>1;
    up(u,v,x,id<<1,l,mid);
    up(u,v,x,id<<1|1,mid+1,r);
    tree[id]=add(tree[id<<1],tree[id<<1|1]);
}

int get(int u,int v,int id=1,int l=1,int r=n){
    if(l>v||r<u) return 0;
    if(u<=l&&r<=v) return tree[id];
    push(id,l,r);
    int mid=(l+r)>>1;
    return add(get(u,v,id<<1,l,mid),get(u,v,id<<1|1,mid+1,r));
}

main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cin>>s;
    n=s.size();
    s=" "+s;
    cin>>q;

    pw[0]=1;
    for(int i=1;i<=n;i++) pw[i]=mul(pw[i-1],base);
    for(int i=1;i<=n;i++) sum[i]=add(sum[i-1],pw[i-1]);

    memset(lz,-1,sizeof lz);
    for(int i=1;i<=n;i++) up(i,i,s[i]-'0');

    while(q--){
        cin>>tp>>u>>v>>x;
        if(tp==1){
            up(u,v,x);
        } else {
            int h1=get(u,u+x-1);
            int h2=get(v,v+x-1);
            if(u<v) h1=mul(h1,pw[v-u]);
            else if(v<u) h2=mul(h2,pw[u-v]);
            cout<<(h1==h2);
        }
    }
}
