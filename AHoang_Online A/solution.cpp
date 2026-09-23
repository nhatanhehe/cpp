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
int n,q,a[N],pos[10000007],last[N],ans[N];
vector<ii>g[N];
vector<int>primes;
int p[10000001];
void sang(){
    for(int i=0;i<=10000000;i++) p[i]=i;
    p[0]=p[1]=0;
    for(int i=2;i*i<=10000000;i++){
        if(p[i]==i)
        for(int j=i*i;j<=10000000;j+=i){
            if(p[j]==j) p[j]=i;
        }
    }
    for(int i=2;i<=10000000;i++) if(p[i]==i) primes.pb(i),pos[i]=primes.size();
}
struct SegmentTree{
    vector<int>tree;
    int n;
    void init(int _n){
        n=_n;
        tree.resize(n*4+5,0);
    }
    void up(int pos,int k,int id=1,int l=1,int r=-1){
        if(r==-1) r=n;
        if(l==r){
            tree[id]=k;
            return;
        }
        int mid=(l+r)>>1;
        if(pos<=mid) up(pos,k,id*2,l,mid);
        else up(pos,k,id*2+1,mid+1,r);
        tree[id]=min(tree[id*2],tree[id*2+1]);
    }
    int walk(int k,int id=1,int l=1,int r=-1){
        if(r==-1) r=n;
        if(l==r) return l;
        int mid=(l+r)>>1;
        if(tree[id*2]<k) return walk(k,id*2,l,mid);
        else if(tree[id*2+1]<k) return walk(k=id*2+1,mid+1,r);
        else return 1e9;
    }
}seg;
void pt(int n,int id){
    while(n>1){
        int h=p[n];
        while(n%h==0) n/=h;
        seg.up(pos[h],id);
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin>>n>>q;
    sang();
    seg.init(primes.size());
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        g[r].pb({l,i});
    }
    for(int i=1;i<=n;i++){
        pt(a[i],i);
        for(auto [l,id]:g[i]){
            ans[id]=seg.walk(l);
            if(ans[id] > (int)primes.size()) ans[id] = (int)primes.size()+1; // clamp to out-of-range
        }
    }
    for(int i=1;i<=q;i++){
        if(ans[i] <= (int)primes.size()){
            cout<<primes[ans[i]-1]<<'\n';
        }else{
            // If no prime found within limit, output a prime beyond limit?
            // For simplicity, output 10000019 (a prime > 1e7) as fallback.
            cout<<10000019<<'\n';
        }
    }
    return 0;
}