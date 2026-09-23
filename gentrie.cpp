#include <bits/stdc++.h>
using namespace std;
#define int long long
// Tên chương trình
const string NAME = "fairnet";
// Số test kiểm tra
const int NTEST = 1000;
const int N=2e5+5;
#define int long long
mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

// Viết lại hàm random để sử dụng cho thuận tiện.
// Hàm random này sinh ngẫu nhiên số trong phạm vi long long
// Số sinh ra nằm trong [L;R].
long long Rand(long long L, long long R) {
    return uniform_int_distribution<int>(L,R)(rd);
}
int h[N],par[N][20];

int lca(int u, int v) {
    if (h[u] < h[v]) swap(u, v);
    for (int i = 19; i >= 0; i--) {
        if (h[u] - h[v] >= (1 << i)) u = par[u][i];
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; i--) {
        if (par[u][i] != par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}

main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    srand(time(NULL));
    freopen("a.inp", "w", stdout);

    int n=Rand(1e4,2e5),q=Rand(1e4,2e5),root=Rand(1,n),w=Rand(1,1e9);
    cout<<n<<" "<<q<<" "<<root<<" "<<w<<'\n';
    h[root]=0;
    vector<int>tree={root};
    vector<int>rem;
    for(int i=1;i<=n;i++){
        if(i!=root) rem.push_back(i);
    }
    random_shuffle(rem.begin(),rem.end());
    while(q--){
        int tp;
        if(tree.size()<n&&tree.size()>=2) tp=Rand(0,1);
        else if(tree.size()>=2) tp=1;
        else tp=0;
        cout<<tp<<' ';
        if(tp==0){
            int p=tree[Rand(0,tree.size()-1)];
            int id=rem.back();
            par[id][0]=p;
            h[id]=h[p]+1;
            for(int j=1;j<=19;j++){
                par[id][j]=par[par[id][j-1]][j-1];
            }
            rem.pop_back();
            int w=Rand(1,1e9);
            tree.push_back(id);
            cout<<p<<" "<<id<<" "<<w<<'\n';
        }
        else{
            int u=tree[Rand(0,tree.size()-1)];
            int v=tree[Rand(0,tree.size()-1)];
            while(v==u) v=tree[Rand(0,tree.size()-1)];
            int k=Rand(1,h[u]+h[v]-2*h[lca(u,v)]+1);
            cout<<u<<" "<<v<<" "<<k<<'\n';
        }
    }
}


