#include<bits/stdc++.h>
using namespace std;
#define task "pktnet"
#define ll long long
#define ii pair<ll, ll>
#define fi first
#define se second
#define all(x) x.begin(),x.end()
const long N = 1e6 + 7;
ll n,k,a[N];
ll f[N][21],g[N][21];
int lg2[N];
inline ll getand(int l,int r){
    int k=lg2[r-l+1];
    return f[l][k]&f[r-(1<<k)+1][k];
}
inline ll getor(int l,int r){
    int k=lg2[r-l+1];
    return g[l][k]|g[r-(1<<k)+1][k];
}
namespace sub3{
    void solve(){
        ll total=0;
        for(int i=1;i<=n;i++){
            int l=1,r=i,ans=1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(getand(mid,i)==0){
                    l=mid+1;
                    ans=mid;
                }
                else r=mid-1;
            }
            if(ans==1) continue;
           // cout<<i<<" "<<ans<<'\n';
            int l1=1,r1=ans-1,res=0;
            while(l1<=r1){
                int mid=(l1+r1)>>1;
                if(getor(mid,ans-1)==(1LL<<k)-1){
                    l1=mid+1;
                    res=mid;
                }
                else r1=mid-1;
            }
            total+=res;
        }
        cout<<total;
    }

}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    freopen(task".INP", "r", stdin);
    freopen(task".OUT", "w", stdout);
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        f[i][0]=a[i];
        g[i][0]=a[i];
    }
    for (int i=1;i<N;i++) lg2[i]=31- __builtin_clz(i);
    for(int j=1;j<=20;j++){
        for(int i=1;i+(1<<(j-1))<=n;i++){
            f[i][j]=(f[i][j-1]&f[i+(1<<(j-1))][j-1]);
            g[i][j]=(g[i][j-1]|g[i+(1<<(j-1))][j-1]);
        }
    }
    sub3::solve();
}
