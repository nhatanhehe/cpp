#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define debug(x) cout<< #x << " = "<< x <<'\n'
#define Task "beauseg"
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf=1e18;
const ll N=1e6+69;
const ll base=256;
const ll mod=1e9+7;
ll add(ll a,ll b)
{
    return (a+b)%mod;
}
ll sub(ll a,ll b)
{
    return ((a-b)%mod+mod)%mod;
}
ll mul(ll a,ll b)
{
    return ((a%mod)*(b%mod))%mod;
}
ll n,k,d,a[N];
ll dp[2][2007][2007];
void solve()
{
    memset(dp,0,sizeof(dp));
    dp[0][0][0]=1;
    for(ll id=0;id<k;id++)
    {
        memset(dp[(id+1)&1],0,sizeof(dp[(id+1)&1]));
        for(ll sum=0;sum<=n;sum++)
        {
            for(ll last=0;last<=n;last++)
            {
                if(dp[id&1][sum][last]==0)
                    continue;
                for(ll i=1;i<=d;i++)
                {
                    ll cur=last+i;
                    if(sum+cur>n)
                        break;
                    dp[(id+1)&1][sum+cur][cur]=add(dp[(id+1)&1][sum+cur][cur],dp[id&1][sum][last]);
                }
            }
        }
    }
    ll ans=0;
    for(ll last=0;last<=n;last++)
        ans=add(ans,dp[k&1][n][last]);
    cout<<ans<<'\n';
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(Task".inp","r"))
    {
        freopen(Task".inp","r",stdin);
        freopen(Task".out","w",stdout);
    }
    cin>>n>>k>>d;
    ll S=sqrt(n);
    k=min(k,S+1);
    solve();
}