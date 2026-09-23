#include <vector>
#include "abperm.h"
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
#define On(mask,i) (mask|(1LL<<i))
#define Off(mask,i) (mask&~(1LL<<i))
namespace personA {
 unsigned long long A2B(vector<int> p){
    vector<int>g[21];
    int n=20;
    vector<vector<ll>>dp(n+2,vector<ll>(1<<20,0));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(__gcd(i,j)==1){
                g[i].pb(j);
            }
        }
    }
    for(int i=1;i<=n;i++) dp[i][1<<(i-1)]=1;
    for(int mask=1;mask<(1<<n);mask++){
        for(int i=1;i<=n;i++){
            if((mask>>(i-1))&1){
                for(int j:g[i]){
                    if((mask>>(j-1))&1){
                        dp[i][mask]+=dp[j][Off(mask,i-1)];
                    }
                }
            }
        }
    }
    ll res=0;
    ll cmask=0;
    ll fmask=(1<<20)-1;
    for(int i=1;i<=n;i++){
        if(i==1){
            // chon tat ca cac so
            for(int j=1;j<p[i-1];j++){
                res+=dp[j][fmask^cmask];
            }
        }
        else{
            for(int j=1;j<=n;j++){
                if(!((cmask>>(j-1))&1)&&__gcd(j,p[i-2])==1&&j<p[i-1]){
                    res+=dp[j][fmask^cmask];
                }
            }
        }
        cmask=On(cmask,p[i-1]-1);
    }
    return res+1;
 }

}
namespace personB {
 vector<int> Btell(unsigned long long _Num){
    vector<int>g[21];
    int n=20;
    vector<vector<ll>>dp(n+2,vector<ll>(1<<20,0));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(__gcd(i,j)==1){
                g[i].pb(j);
            }
        }
    }
    for(int i=1;i<=n;i++) dp[i][1<<(i-1)]=1;
    for(int mask=1;mask<(1<<n);mask++){
        for(int i=1;i<=n;i++){
            if((mask>>(i-1))&1){
                for(int j:g[i]){
                    if((mask>>(j-1))&1){
                        dp[i][mask]+=dp[j][Off(mask,i-1)];
                    }
                }
            }
        }
    }
    set<int>s;
    for(int i=1;i<=n;i++){
        s.insert(i);
    }
    ll res=0;
    ll cmask=0;
    ll fmask=(1<<20)-1;
    vector<int>ans;
    for(int i=1;i<=n;i++){
        if(i==1){
            for(int j=1;j<=n;j++){
                ll tmp=dp[j][fmask^cmask];
                if(_Num>tmp) _Num-=tmp;
                else{
                    ans.pb(j);
                    s.erase(j);
                    cmask=On(cmask,j-1);
                    break;
                }
            }
        }
        else{
            for(int j:s){
                if(!((cmask>>(j-1))&1)&&__gcd(j,ans.back())==1){
                    ll tmp=dp[j][fmask^cmask];
                    if(_Num>tmp) _Num-=tmp;
                    else{
                        ans.pb(j);
                        s.erase(j);
                        cmask=On(cmask,j-1);
                        break;
                    }
                }
            }
        }
    }
    return ans;
 }
}
