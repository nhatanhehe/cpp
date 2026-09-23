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
const ll N=1e6+5;
const ll mod=1e9+7;
const ll base=311;
const ll phainon=33550336;
#define On(mask,i) (mask||(1LL<<i))
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
int n,q,a[N],pos[1000007],last[N],ans[N],x,cnt[N];
vector<ii>g[N];
vector<int>primes[N],num[N];
int p[10000005];
set<int>s[N];
void sang(){
    for(int i=2;i<=1e6;i++){
        for(int j=i;j<=1e6;j+=i){
            primes[j].pb(i);
        }
    }
}
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    sang();
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]<=1) continue;
        num[a[i]].pb(i);
        for(int uoc:primes[a[i]]) cnt[uoc]++;
    }
    for(int i=1;i<=q;i++){
        cin>>x;
        if(x<=1||!cnt[x]) continue;
        for(int k=1;k*x<=1e6;k++){
            int u=k*x;
            if(num[u].empty()) continue;
            int v=k;
            int num_sz=num[u].size();
            for(int uoc:primes[u]) cnt[uoc]-=num_sz;
            for(int uoc:primes[v]) cnt[uoc]+=num_sz;
            if(num[v].empty()) swap(num[u],num[v]);
            else{
                if(num[u].size()<num[v].size()){
                    while(num[u].size()){
                        num[v].pb(num[u].back()); num[u].pop_back();
                    }
                }
                else{
                    while(num[v].size()){
                        num[u].pb(num[v].back()); num[v].pop_back();
                    }
                    swap(num[u],num[v]);
                }
            }
        }
    }
    for(int i=1;i<=1e6;i++){
        for(int id:num[i]) a[id]=i;
    }
    for(int i=1;i<=n;i++) cout<<a[i]<<" ";
}