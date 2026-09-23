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
const int N=4e6+5,lg=30,mod=1e9+7;
int node,query,r[N],heig[N],tong,sz[N],pre[N],dinh,cur[N];
set<int>ver[N];
bool k[N];
int acs(int u){
  return u==r[u]?u:acs(r[u]);
}
void join(int u,int v){
  u=acs(u);
  v=acs(v);
  if(u!=v){
    if(heig[u]<heig[v])swap(u,v);
    r[v]=u;
    heig[u]+=(heig[u]==heig[v]);
    tong+=sz[u]*sz[v];
    sz[u]+=sz[v];
  }
}
void del(int u,int v,int timer){
    queue<int>p;
    k[u]=1;
    k[v]=1;
    vector<int>res,res1;
    p.em(u);
    while(!p.empty()){
      int u=p.front();
      res.emb(u);
      p.pop();
      for(auto v:ver[u]){
        if(!k[v]){
          p.em(v);
          k[v]=true;
        }
      }
    }
    p.em(v);
    while(!p.empty()){
      int u=p.front();
      res1.emb(u);
      p.pop();
      for(auto v:ver[u]){
        if(!k[v]){
          p.em(v);
          k[v]=true;
        }
      }
    }
    pre[timer]+=sz(res)*sz(res1);
    for(int i:res){
      r[i]=u;k[i]=false;
      // cout <<i<<" ";
    }
    // cout<<'\n';
    r[u]=u;
    sz[u]=sz(res);
    heig[u]=1;
    for(int i:res1){
      // cout <<i<<" ";
      r[i]=v;k[i]=false;
    }
    heig[v]=1;
    r[v]=v;
    sz[v]=sz(res1);
}
bool M2;
void solve(){
  int t=0;
  cin >> t >>node >> query;
  dinh=node;
  for(int i=1;i<=node;++i){
    r[i]=i;
    sz[i]=1;
  }
  int ans=0;
  for(int _=1;_<=query;_++){
    int type,x,y;
    cin >> type >> x;
    pre[_]=pre[_-1];
    ans*=t;
    // type=ans;
    x^=ans;
    if(type==1){
      cin >> y;
      y^=ans;
      ver[x].insert(y);
      ver[y].insert(x);
      join(x,y);
    }
    if(type==2){
      cin >> y;
      y^=ans;
      ver[x].erase(y);
      ver[y].erase(x);
      del(x,y,_);
    }
    if(type==3){
       ans=tong-pre[_-x];
       cout << ans<<'\n';
    }
    // cout <<type<<" "<<x<<" ";
    // if(type!=3)
    // cout <<y;
    // cout<<'\n';
  }

}
main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    #define task "aws"
    if(fopen(task".inp","r")){
      freopen(task".inp","r",stdin);
      freopen(task".out","w",stdout);
    }
    int t=1;
 //   cin >> t;
while(t--){
    solve();
}
look_memory;
look_time;
}
