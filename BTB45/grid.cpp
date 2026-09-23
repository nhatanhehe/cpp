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
int n,q,a[3][N],wa[3][N];
struct OP{
    int r1,c1,r2,c2;
};
vector<OP>res;
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cin>>n>>q;
    vector<int>bd;
    for(int i=1;i<=2;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            if(i==1&&a[i][j]>n) wa[i][j]=1;
        }
    }
    while(1){
        int f=0,st;
        for(int j=1;j<=n;j++){
            if(a[2][j]<=n){
                f=1;
                st=j;
                break;
            }
        }
        if(!f) break;
        int WA;
        for(int i=1;i<=n;i++){
            if(wa[1][i]){
                WA=i;
                break;
            }
        }
        if(WA==st){
            swap(a[1][WA],a[2][st]);
            res.pb({1,WA,2,st});
            wa[1][WA]=0;
            continue;
        }
        else if(WA<st){
            while(st>WA){
                swap(a[2][st-1],a[2][st]);
                res.pb({2,st-1,2,st});
                st--;
                if(WA==st){
                    swap(a[1][WA],a[2][st]);
                    res.pb({1,WA,2,st});
                    wa[1][WA]=0;
                    break;
                }
            }
        }
        else{
            while(st<WA){
                swap(a[2][st+1],a[2][st]);
                res.pb({2,st+1,2,st});
                st++;
                if(WA==st){
                    swap(a[1][WA],a[2][st]);
                    res.pb({1,WA,2,st});
                    wa[1][WA]=0;
                    break;
                }
            }
        }
    }
    for(int i=1;i<=2;i++){
        while(1){
            bool f=0;
            int st,en;
            //for(int j=1;j<=n;j++) cerr<<a[i][j]<<' ';
            for(int j=1;j<=n;j++){
                if(a[i][j]!=(i-1)*n+j){
                    f=1;
                    st=j;
                    en=a[i][j]-(i-1)*n;
                    break;
                }
            }
            //cerr<<st<<" "<<en<<'\n';
            if(!f) break;
            while(st<en){
                swap(a[i][st+1],a[i][st]);
                res.pb({i,st+1,i,st});
               st++;
            }
            while(st>en){
                swap(a[i][st-1],a[i][st]);
                res.pb({i,st-1,i,st});
                st--;
            }
            ///break;
        }
    }
    cout<<res.size()<<'\n';
    for(OP x:res){
        if(x.r1>x.r2) swap(x.r1,x.r2);
        if(x.c1>x.c2) swap(x.c1,x.c2);
        cout<<x.r1<<" "<<x.c1<<" "<<x.r2<<" "<<x.c2<<'\n';
    }
}
