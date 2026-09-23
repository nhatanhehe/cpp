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
ll n,d,l,x=0,y=0,on_line=0;
vector<ii>c;
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>d>>l;
        if(d==1){
            y+=l;
        }
        if(d==2){
            x+=l;
        }
        if(d==3){
            x+=l;
            y-=l;
        }
        if(d==4){
            y-=l;
        }
        if(d==5){
            x-=l;
        }
        if(d==6){
            x-=l;
            y+=l;
        }
            on_line+=l;
        c.pb({x,y});
    }
    c.pb(c[0]);
    ld S=0;
    for(int i=0;i<c.size()-1;i++){
        S += (c[i].fi * c[i+1].se - c[i+1].fi * c[i].se);
    }
    S=abs(S)/2;
    ld result=S-on_line*0.5+1;
    cout<<result+on_line;
}
