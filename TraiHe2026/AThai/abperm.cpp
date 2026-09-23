#include<bits/stdc++.h>
#include "abperm.h"
using namespace std;
#define ll long long
#define int long long
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
namespace personA {
    unsigned ll f[1000006];
void cal(){
    f[0]=1;
    for(int i=1;i<=30;i++){
        f[i]=f[i-1]*i;
    }
}
     unsigned long long A2B(vector<int> p){
    cal();
    int n=p.size();
    unsigned ll res=0;
    for(int i=1;i<n;i++) res+=f[i];
    for(int i=1;i<=n;i++){
        unsigned ll cnt=0;
        for(int j=i+1;j<=n;j++){
            if(p[i-1]>p[j-1]){
                cnt++;
            }
        }
        res+=cnt*f[n-i];
    }
    return res+1;
 }
}
namespace personB {
    unsigned ll f[1000006];
void cal(){
    f[0]=1;
    for(int i=1;i<=30;i++){
        f[i]=f[i-1]*i;
    }
}
 vector<int> Btell(unsigned long long _Num){
    cal();
    int n;
    for(int i=1;i<=20;i++){
        if(_Num>f[i]) _Num-=f[i];
        else{
            n=i;
            break;
        }
    }
    set<int>s;
    for(int i=1;i<=n;i++){
        s.insert(i);
    }
    vector<int>res;
    for(int i=1;i<=n;i++){
        for(int x:s){
            ll ways=f[n-i];
            if(_Num>ways) _Num-=ways;
            else{
                res.pb(x);
                s.erase(x);
                break;
            }
        }
    }
    return res;
 }
}
