#include<bits/stdc++.h>
#define ll long long
#define N 1000006
using namespace std;
ll a[N],n,ans=0,i,j,k,l,r,m,d;
ll kt(ll x)
{
    if(x%2!=0)
        return 0;
    ll sum=0;
    while(x>0)
    {
        sum+=x%10;
        x=x/10;
    }
    if(sum%2==0)
        return 1;
    return 0;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
//    freopen("a.inp","r",stdin);
//    freopen("a.out","w",stdout);
    cin>>l>>r;
    while(l%20!=0)
    {
        ans+=kt(l);
        l++;
    }
    while(r%20!=19)
    {
        ans+=kt(r);
        r--;
    }
    ans+=(r-l+1)/20*5;
    cout<<ans;
}
