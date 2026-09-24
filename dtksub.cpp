#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define ii pair<int,int>
#define iii pair<int,pair<int,int>>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const int inf=1e18;
const int N=2e5+5;
const int mod1=1e9+7;
const int mod2=1e9+9;
const int base1=311;
const int base2=317;
#define On(mask,i) (mask|(1LL<<i))
#define Off(mask,i) (mask^(1LL<<i))
inline int mul(int a,int b,int mod){
    return (a%mod)*(b%mod)%mod;
}
inline int sub(int a,int b,int mod){
    return ((a-b)%mod+mod)%mod;
}
inline int add(int a,int b,int mod){
    return (a%mod+b%mod)%mod;
}
int k,n;
int pw1[N],pw2[N];
int has1[N],has2[N];
string s;
ii geth(int l,int r){
    int h1=sub(has1[r],mul(has1[l-1],pw1[r-l+1],mod1),mod1);
    int h2=sub(has2[r],mul(has2[l-1],pw2[r-l+1],mod2),mod2);
    return {h1,h2};
}
bool check(int x){
    vector<ii> vals;
    vals.reserve(n-x+1);
    for(int i=x;i<=n;i++) vals.pb(geth(i-x+1,i));
    sort(all(vals));
    int cnt=0;
    for(int i=0;i<(int)vals.size();i++){
        if(i==0||vals[i]==vals[i-1]) cnt++;
        else cnt=1;
        if(cnt>=k) return true;
    }
    return false;
}
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin>>s>>k;
    n=s.size();
    s=" "+s;
    pw1[0]=1;
    pw2[0]=1;
    for(int i=1;i<=n;i++){
        pw1[i]=mul(pw1[i-1],base1,mod1);
        pw2[i]=mul(pw2[i-1],base2,mod2);
    }
    for(int i=1;i<=n;i++){
        has1[i]=add(mul(has1[i-1],base1,mod1),s[i]-'a'+1,mod1);
        has2[i]=add(mul(has2[i-1],base2,mod2),s[i]-'a'+1,mod2);
    }
    int l=1,r=n,mid,ans=0;
    while(l<=r){
        mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else r=mid-1;
    }
    cout<<ans;
}