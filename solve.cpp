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
ll n,q,t,a[N],b[N],c[N],out[N],vis[N],in[N],cur,coins[N],dp[N];
vector<vector<int>>vec;
vector<int>g[N];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cout << "Debug: program started" << endl;
    cin>>n>>q>>t;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=q;i++){
        cin>>b[i]>>c[i];
        in[c[i]]++;
        out[b[i]]=c[i];
    }
    for(int i=1;i<=n;i++){
        if(!in[i]){
            int j=i;
            ll sum=a[i],base=a[i];
            while(out[j]){
                t-=base;
                coins[++cur]=sum;
                j=out[j];
                sum+=a[j];
                base+=a[j];
            }
            coins[++cur]=sum;
        }
    }
    if(cur<n||t<0) return cout<<0,0;
    dp[0]=1;
    for(int i=1;i<=cur;i++){
        for(int j=0;j<=t;j++){
            if(j>=coins[i]){
                dp[j]=add(dp[j],dp[j-coins[i]]);
            }
        }
    }
    cout<<dp[t];
}