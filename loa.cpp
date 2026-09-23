#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define Task "circle"
#define ii pair<ll,ll>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf=1e18;
const ll N=2e5+5;

ii co[N];

inline ld sq(ld x){return x*x;}
inline ld dist(ld x,ld y,ld u,ld v){return sqrt((double)(sq(u-x)+sq(v-y)));}

ll ccw(ii a,ii b,ii c){
    return (b.fi-a.fi)*(c.se-a.se)-(b.se-a.se)*(c.fi-a.fi);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int n;cin>>n;
    for(int i=1;i<=n;i++)cin>>co[i].fi>>co[i].se;
    if(n==1){
        cout<<fixed<<setprecision(3)<<0.000<<'\n';
        return 0;
    }
    const ld eps=1e-12L;
    ld ans=1e30L;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            ld ux=(co[i].fi+co[j].fi)/2.0L;
            ld uy=(co[i].se+co[j].se)/2.0L;
            ld R=dist(ux,uy,co[i].fi,co[i].se);
            bool ok=1;
            for(int t=1;t<=n;t++){
                if(dist(ux,uy,co[t].fi,co[t].se)>R+1e-9L){ok=0;break;}
            }
            if(ok)ans=min(ans,R);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            for(int k=j+1;k<=n;k++){
                if(ccw(co[i],co[j],co[k])==0)continue;
                ld D=2.0L*((ld)co[i].fi*((ld)co[j].se-(ld)co[k].se)
                          +(ld)co[j].fi*((ld)co[k].se-(ld)co[i].se)
                          +(ld)co[k].fi*((ld)co[i].se-(ld)co[j].se));
                if(fabsl(D)<eps)continue;
                ld x1s=sq((ld)co[i].fi)+sq((ld)co[i].se);
                ld x2s=sq((ld)co[j].fi)+sq((ld)co[j].se);
                ld x3s=sq((ld)co[k].fi)+sq((ld)co[k].se);
                ld ux=(x1s*((ld)co[j].se-(ld)co[k].se)
                      +x2s*((ld)co[k].se-(ld)co[i].se)
                      +x3s*((ld)co[i].se-(ld)co[j].se))/D;
                ld uy=(x1s*((ld)co[k].fi-(ld)co[j].fi)
                      +x2s*((ld)co[i].fi-(ld)co[k].fi)
                      +x3s*((ld)co[j].fi-(ld)co[i].fi))/D;
                ld R=dist(ux,uy,co[i].fi,co[i].se);
                bool ok=1;
                for(int t=1;t<=n;t++){
                    if(dist(ux,uy,co[t].fi,co[t].se)>R+1e-9L){ok=0;break;}
                }
                if(ok)ans=min(ans,R);
            }
        }
    }
    if(ans>1e29L)ans=0.0;
    cout<<fixed<<setprecision(3)<<ans<<'\n';
    return 0;
}
