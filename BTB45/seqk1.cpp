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
ll n,k;
ll t;
namespace sub1{
    vector<string>res;
    void ql(int i,int last,int cnt,string s){
        if(cnt>k) return;
        if(i>n){
            if(cnt==k){
                res.pb(s);
            }
            return;
        }
        // chon 0
        ql(i+1,0,cnt,s+"0");
        // chon 1
        if(last) ql(i+1,1,cnt,s+"1");
        else ql(i+1,1,cnt+1,s+"1");
    }
    void solve(){
        int t;
        cin>>t;
        ql(1,0,0,"");
        sort(all(res));
        cout<<res.size()<<"\n"<<res[t-1];
    }
}
namespace sub2{
    ll dp[200][2][200];
    ll calc(int i,int last,int cnt){
        ll &ans=dp[i][last][cnt];
        if(cnt>k){
            ans=0;
            return ans;
        }
        if(i>n){
            if(cnt==k){
                ans=1;
                return ans;
            }
            else{
                ans=0;
                return ans;
            }
        }
        if(ans!=-1) return ans;
        ans=0;
        // chon 0
        ans=ans+calc(i+1,0,cnt);
        // chon 1
        if(last==0&&cnt<k) ans=ans+calc(i+1,1,cnt+1);
        else if(last==1) ans=ans+calc(i+1,1,cnt);
        return ans%111539786;
    }
    void solve(){
        for(int i=0;i<=130;i++){
            for(int j=0;j<=1;j++){
                for(int c=0;c<=130;c++) dp[i][j][c]=-1;
            }
        }
        cout<<calc(1,0,0)<<'\n';
    }
}
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    while(cin>>n>>k){

        sub2::solve();
    }
}
