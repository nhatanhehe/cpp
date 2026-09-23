#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
//using namespace __gnu_pbds;
#define LongDepTrai "task"
#define ll long long
#define int long long
#define ull unsigned long long
#define ld long double
#define ii pair<int,int>
#define iii pair<int,ii>
#define iv pair<ii,ii>
#define pll pair<ll,ll>
#define vi vector<int>
#define vii vector<ii>
#define vll vector<ll>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) int((x).size())
#define order_set(T) tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>

inline ll add(ll a, ll b, ll mod)
{
    a += b;
    if(a >= mod) a -= mod;
    return a;
}
inline ll sub(ll a, ll b, ll mod)
{
    a -= b;
    if(a < 0) a += mod;
    return a;
}
inline ll mul(ll a, ll b, ll mod)
{
    return ( (ll)a * b ) % mod;
}

static mt19937_64 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());
const int N=1e5+9;
const int mod=1e9+7;
int n,m,a[N],ans=0;
vii g[N];
map<int,int> d[N],f[N];
int res=1e18;

void dijk()
{
    priority_queue<iii,vector<iii>,greater<iii>> q;
    d[1][-1]=0;
    for(ii x:g[1])
    {
        int w=x.se;
        int v=x.fi;

        d[v][-1]=w;
        f[v][-1]=1;
        q.push({d[v][-1],{v,-1}});
    }
    a[n]=n+1;
    while(q.size())
    {
        int z=q.top().se.fi;
        int col=q.top().se.se;
        int cost=q.top().fi;
        q.pop();
//        cout<<z<<" "<<col<<" "<<cost<<"\n";
        if (!d[z].count(col) || d[z][col] != cost) continue;

        for(ii x:g[z])
        {
            int w=x.se;
            int v=x.fi;
            if(v==1) continue;
            if(v==n)
            {
//                if(col==-1) continue;
                if(res>cost+w)
                {
                    res=cost+w;
                    ans=f[z][col];
                }
                else if(res==cost+w)
                {
                    ans=(ans+f[z][col])%mod;
                }
                continue;
            }
            if(col==-1)
            {
                if(a[v]!=a[z])
                {
                    if(!d[v].count(a[z]))
                    {
                        d[v][a[z]]=cost+w;
                        f[v][a[z]]=f[z][col];
                        q.push({d[v][a[z]],{v,a[z]}});
                    }
                    else if(d[v][a[z]]==cost+w)
                    {
                        f[v][a[z]]=(f[v][a[z]]+f[z][col])%mod;
                    }
                }
                else if(a[v]==a[z])
                {
                    if(!d[v].count(col))
                    {
                        d[v][col]=cost+w;
                        f[v][col]=f[z][col];
                        q.push({d[v][col],{v,col}});
                    }
                    else if(d[v][col]==cost+w)
                    {
                        f[v][col]=(f[v][col]+f[z][col])%mod;
                    }
                }

            }
            else if(a[v]==col)
            {
                if(!d[v].count(a[z]))
                {
                    d[v][a[z]]=cost+w;
                    f[v][a[z]]=f[z][col];
                    q.push({d[v][a[z]],{v,a[z]}});
                }
                else if(d[v][a[z]]==cost+w)
                {
                    f[v][a[z]]=(f[v][a[z]]+f[z][col])%mod;
                }
            }
            else if(a[v]==a[z])
            {
                if(!d[v].count(col))
                {
                    d[v][col]=cost+w;
                    f[v][col]=f[z][col];
                    q.push({d[v][col],{v,col}});
                }
                else if(d[v][col]==cost+w)
                {
                    f[v][col]=(f[v][col]+f[z][col])%mod;
                }
            }
        }
    }
}
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    if(fopen(LongDepTrai".inp","r"))
    {
        freopen(LongDepTrai".inp","r",stdin);
        freopen(LongDepTrai".out","w",stdout);
    }
    cin>>n>>m;
    for(int i=2; i<n; i++)
    {
        cin>>a[i];
    }
    for(int i=1; i<=m; i++)
    {
        int u,v,c;
        cin>>u>>v>>c;
        g[u].pb({v,c});
        g[v].pb({u,c});
    }
    dijk();
    cout<<res<<"\n"<<ans;

    return 0;
}
