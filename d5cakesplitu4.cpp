#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
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

int m,n,k,cnt_l,cnt_r,dist[N],mx[N],my[N];
vector<int>g[N];
vector<ii>adj[N];
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
ii tr[N];
struct res{
    int x,y,u,v;
};
ll H(int x,int y){
    return x*10000000LL+y;
}
unordered_map<ll,vector<res>>mp;
vector<int>euler;
int used[N],vis[N];

// DFS cho Euler
void DFS(int u){
    vis[u]=1;
    while(adj[u].size()){
        auto [v,id]=adj[u].back();
        adj[u].pop_back();
        if(used[id]) continue;
        used[id]=1;
        DFS(v);
    }
    euler.pb(u);
}

// DFS-based augmenting path
bool dfs_match(int u){
    for(int v : g[u]){
        if(vis[v]) continue;
        vis[v] = 1;
        if(!my[v] || dfs_match(my[v])){
            mx[u] = v;
            my[v] = u;
            return true;
        }
    }
    return false;
}

// Matching greedy thuần túy
void greedy_matching(){
    for(int u = 1; u <= cnt_l; u++){
        if(mx[u]) continue;
        fill(vis, vis + cnt_r + 1, 0);
        dfs_match(u);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);

    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }

    cin>>m>>n>>k;
    vector<vector<int>>choco(m+2,vector<int>(n+1,0));
    vector<vector<int>>mat(m+2,vector<int>(n+1,0));
    for(int i=1;i<=k;i++){
        int x,y;
        cin>>x>>y>>choco[x][y];
        if((x+y)&1){
            mat[x][y]=++cnt_l;
            tr[cnt_l]={x,y};
        }
    }
    cnt_r=cnt_l;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(choco[i][j]&&(i+j)%2==0){
                mat[i][j]=++cnt_r;
                tr[cnt_r]={i,j};
            }
        }
    }

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(choco[i][j]&&(i+j)%2!=0){
                for(int k2=0;k2<4;k2++){
                    int x=i+dx[k2],y=j+dy[k2];
                    if(1<=x&&x<=m&&1<=y&&y<=n&&choco[x][y]){
                        g[mat[i][j]].pb(mat[x][y]);
                    }
                }
            }
        }
    }

    // Thực hiện matching
    greedy_matching();

    // Gom kết quả
    int cnt=0;
    for(int i=1;i<=cnt_l;i++){
        if(mx[i]){
            int col1=choco[tr[i].fi][tr[i].se];
            int col2=choco[tr[mx[i]].fi][tr[mx[i]].se];
            if(col1>col2) swap(col1,col2);
            mp[H(col1,col2)].pb({tr[i].fi,tr[i].se,tr[mx[i]].fi,tr[mx[i]].se});
            cnt++;
            adj[col1].pb({col2,cnt});
            adj[col2].pb({col1,cnt});
        }
    }

    vector<res>ans;
    fill(vis, vis + k + 1, 0);
    for(int j=1;j<=k;j++){
        if(!vis[j]){
            DFS(j);
            for(int i=0;i<euler.size()-1;i++){
                if(i%2==0){
                    int x=euler[i];
                    int y=euler[i+1];
                    if(x>y) swap(x,y);
                    ans.pb(mp[H(x,y)].back());
                    mp[H(x,y)].pop_back();
                }
            }
            euler.clear();
        }
    }

    for(auto [x,y,u,v]:ans){
        cout<<x<<" "<<y<<" "<<u<<" "<<v<<'\n';
    }
}
