#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define debug(x) cout<< #x << " = "<< x <<'\n'
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf=1e18;
const ll N=1e6+5;
const ll mod=1e9+7;
const ll base=311;
const ll phainon=33550336;
#define On(mask,i) (mask(1LL<<i))
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
string s[N];
int n,R,C,range[N],nxt[N][23];
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    #define Task "a"
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cin>>n>>R>>C;
    for(int i=1;i<=n;i++){
        cin>>s[i];
    }
    int sum=0,r=n;
    for(int l=n;l>=1;l--){
        sum+=s[l].size();
        while(sum+r-l>C){
            sum-=s[r].size();
            r--;
        }
        if(r>=l) nxt[l][0]=r+1;
        else nxt[l][0]=l;
    }
    nxt[n+1][0]=n+1;
//    cout<<"12132 "<<nxt[2][0]<<'\n';
//    cout<<0<<": \n";
//        for(int i=1;i<=n;i++) cout<<nxt[i][0]<<" ";
//        cout<<'\n';
    for(int j=1;j<=20;j++){
        for(int i=1;i<=n+1;i++) nxt[i][j]=nxt[nxt[i][j-1]][j-1];
//        cout<<j<<": \n";
//        for(int i=1;i<=n+1;i++) cout<<nxt[i][j]<<" ";
//        cout<<'\n';
    }
    int mx=0,it1,it2;
    for(int i=1;i<=n;i++){
        int u=i;
        //cout<<i<<": ";
        for(int j=20;j>=0;j--){
            if((R>>j)&1){
                //cout<<R<<" ";
                u=nxt[u][j];
               // cout<<j<<" "<<u<<"\n";
            }
        }
        if(mx<u-i){
            mx=u-i;
            it1=i;
            it2=u-1;
        }
    }
    //cout<<it1<<" "<<it2<<'\n';
    int cnt=it1,S=0;
    vector<vector<string>>ans;
    vector<string>res;
    for(int i=it1;i<=it2;i++){
        S+=s[i].size();
        if(S+i-cnt>C){
            cnt=i;
            S=s[i].size();
            ans.pb(res);
            res.clear();
            res.pb(s[i]);
        }
        else res.pb(s[i]);
    }
    if(res.size())ans.pb(res);
    //cout<<ans.size();
    for(auto x:ans){
        for(int i=0;i<x.size();i++){
            cout<<x[i];
            if(i!=x.size()-1) cout<<" ";
        }
        cout<<'\n';
    }
}



