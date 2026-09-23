#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
typedef long double ld;
#define pb push_back
#define pf push_front
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
#define On(mask,i) (mask|(1LL<<i))
#define Off(mask,i) (mask^(1LL<<i))
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
int n,X,Y,U,V,dis1[N],dis2[N];
ii cord[N];
int dist(int x,int y,int u,int v){
    return (u-x)*(u-x)+(y-v)*(y-v);
}
multiset<ii>d1,d2,d3,d4;

main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cin>>n>>X>>Y>>U>>V;
    for(int i=1;i<=n;i++){
        cin>>cord[i].fi>>cord[i].se;
        dis1[i]=dist(cord[i].fi,cord[i].se,X,Y);
        dis2[i]=dist(cord[i].fi,cord[i].se,U,V);
        d1.insert({dis1[i],i});
        d2.insert({dis2[i],i});
    }
    d3=d1;
    d4=d2;
    int ans=inf;
    for(auto [r1,idx]:d1){
        auto it = d2.find(ii(dis2[idx], idx));
        if (it != d2.end()) d2.erase(it);
        if(d2.size()){
            int r2=d2.rbegin()->fi;
            ans=min(ans,r1+r2);
        }
        else ans=min(ans,r1);
    }
    for(auto [r2,idx]:d4){
        auto it=d3.find(ii(dis1[idx], idx));
        if (it!=d3.end())d3.erase(it);
        if(d3.size()){
            int r1=d3.rbegin()->fi;
            ans=min(ans,r1+r2);
        }
        else ans=min(ans,r2);
    }
    cout<<fixed<<setprecision(0)<<ans;
}
