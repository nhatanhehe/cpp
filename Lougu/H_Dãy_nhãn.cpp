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

// SỬA LỖI 1: Tăng kích thước mảng để khớp với maxn = 2e6 trong hàm precum()
const ll N=2e6+5; 
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

int n,m;
ll f[N],inv[N];

ll exp(ll a,ll n){
    if(n==0) return 1;
    if(n==1) return a;
    ll t=exp(a,n/2);
    t=mul(t,t);
    if(n&1) return mul(t,a);
    return t;
}

void precum(){
    f[0]=inv[0]=1;
    int maxn=2e6;
    for(int i=1;i<=maxn;i++){
        f[i]=mul(f[i-1],i);
    }
    inv[maxn]=exp(f[maxn],mod-2);
    for(int i=maxn-1;i>=1;i--){
        inv[i]=mul(inv[i+1],i+1);
    }
}

ll nCk(int n,int k){
    if(k<0||n<0||n<k) return 0;
    return mul(f[n],mul(inv[k],inv[n-k]));
}

main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    precum();
    if (!(cin>>n>>m)) return 0;
    
    ll res=0;
    for(int i=1;i<=n;i++){
        // SỬA LỖI 2: Áp dụng số lượng tiền tố hợp lệ trong n! hoán vị là (n+1)! / (i+1)
        ll ways = nCk(m-i, n-i);
        ll hoan_vi_hop_le = mul(f[n+1], inv[i+1]);
        
        res = add(res, mul(ways, hoan_vi_hop_le));
    }
    cout<<res;
}