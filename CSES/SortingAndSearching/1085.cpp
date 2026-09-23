#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define debug(x) cout<< #x << " = "<< x <<'\n'
#define Task "memories"
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf=1e18;
const ll N=2e6+5;
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
ll n,a[N],k;
bool check(ll x){
    ll sum=0;
    int j=1;
    vector<int>dp(n+3,1e9);
    dp[0]=0;
    deque<ii>dq;
    dq.pb(ii(0,0));
    for(int i=1;i<=n;i++){
        sum+=a[i];
        while(sum>x){
            sum-=a[j];
            j++;
        }
        while(dq.size()&&dq.front().se<j-1) dq.pop_front();
        if(dq.size()){
            dp[i]=dq.front().fi+1;
            while(dq.size()&&dq.back().fi>=dp[i]) dq.pop_back();
            dq.pb(ii(dp[i],i));
        }
    }
    return dp[n]<=k;
}
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];

    }
    ll l=1,r=1e18,ans;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(check(mid)){
            r=mid-1;
            ans=mid;
        }
        else l=mid+1;
    }
    cout<<ans;
}
