
#include<bits/stdc++.h>
using namespace std;
bool M1;
#define int long long
#define PI 3.14159265358979323846
#define sz(a) (int)a.size()
#define all(x) x.begin(),x.end()
#define ii pair<int,int>
#define iii pair<int,ii>
#define iv pair<ii,ii>
#define se second
#define fi first
#define ffi fi.fi
#define sfi se.fi
#define sse se.se
#define fse fi.se
#define lt(i, c, d) for(int i = c; i <= d; ++i)
#define fl(i, c, d) for(int i = d; i >= c; --i)
#define pb push_back
#define emb emplace_back
#define emf emplace_front
#define em emplace
#define look_memory cerr<<abs(&M2-&M1)/1024.0/1024<<'\n'
#define look_time   cerr << "TIME : " << clock() * 0.001 << "s" <<'\n'
const int N=5e4+5,lim=243+5;
int node,query,a[N],l[N],dp[N][lim],r[N],po[N];
bool ok[N];
int mu(int x){
    return po[x];
}
int bit(int g,int x){
    return (g/po[x])%3;
}
bool kiemtra(int mask){
    int sl=0;
    for(int i=0;i<query;++i){
        int g=bit(mask,i);
        if(g==1)++sl;
    }
    return sl<=1;
}
bool check(int mask){
    for(int i=0;i<query;++i){
        int g=bit(mask,i);
        if(g==1)return false;
    }
    return true;
}
bool M2;
main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    #define task "aws"
    if(fopen(task".inp","r")){
      freopen(task".inp","r",stdin);
      freopen(task".out","w",stdout);
    }
    cin >> node >> query;
    int sum=0;
    po[0]=1;
    for(int i=1;i<=6;++i)po[i]=po[i-1]*3;
    // cout <<bit(8,0)<<'\n';
    for(int i=1;i<=node;++i)cin >> a[i],sum+=a[i];
    for(int i=0;i<query;++i)cin >> l[i] >> r[i];
    for(int j=0;j<mu(query);++j){
        ok[j]=kiemtra(j);
    }
    // memset(dp,-0x3f,sizeof dp);
    for(int i=0;i<=node;++i){
        for(int j=0;j<=mu(query);++j)dp[i][j]=-1e18;
    }
    dp[0][0]=0;
    for(int i=1;i<=node;++i){
        for(int mask=0;mask<mu(query);++mask){
            if(dp[i-1][mask]==-1e18)continue;
            // dp[i][mask]=dp[i-1][mask];
            if(check(mask))dp[i][mask]=max(dp[i][mask],dp[i-1][mask]);
            for(int j=0;j<query;++j){
                if(l[j]<=i&&i<=r[j]){
                    int x=bit(mask,j);
                    if(x==2)continue;
                    int nmask=mask-po[j]*x+po[j];
                    if(ok[nmask])
                    dp[i][nmask]=max(dp[i][nmask],dp[i-1][mask]+(query-j)*a[i]);
                    // if(dp[i][nmask]==118&&i==8)
                    // cout <<i<<" "<<mask<<" "<<nmask<<" "<<(query-j)*a[i]<<" "<<dp[i-1][mask]<<" "<<dp[i][nmask]<<'\n';
                }
            }
            // if(dp[i][mask]==158)
            // cout << i<<" "<<mask<<" "<<dp[i][mask]<<'\n';

            // if(mask==2&&i==4)cout <<dp[i][mask]<<" ";
        }
        for(int mask=0;mask<mu(query);++mask){
            if(dp[i][mask]==-1e18)continue;
            for(int j=0;j<query;++j){
                if(l[j]<=i){
                    int x=bit(mask,j);
                    int nmask=mask-po[j]*x+po[j]*2;
                    dp[i][nmask]=max(dp[i][nmask],dp[i][mask]);
                }
            }
        }
    }
    // for(int i=1;i<=node;++i){
        // for(int mask=0;mask<mu(query);++mask)
            // if(i==node&&dp[i][mask]==158)cout <<i<<" "<<mask<<" "<<dp[i][mask]<<'\n';
    // }
    // cout <<dp[node][2];
    // cout <<sum*query<<'\n';
    cout <<sum*query-dp[node][mu(query)-1];
look_memory;
look_time;
}
Viết cho Thanh Tu
