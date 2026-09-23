#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
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
const ll N=3e5+5;
const ll mod=1e9+7;
const ll base=311;
#define On(mask,i) (mask|(1LL<<i))
#define Off(mask,i) (mask^(1LL<<i))
mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

// Viết lại hàm random để sử dụng cho thuận tiện.
// Hàm random này sinh ngẫu nhiên số trong phạm vi long long
// Số sinh ra nằm trong [L;R].
long long Rand(long long L, long long R) {
    assert(L <= R);
    return L + rd() % (R - L + 1);
}
int m,n,t,a[N];
main(){
    srand(time(NULL));
    //cout<<(t=Rand(1,1))<<'\n';
    t=1;
    while(t--){
        n=Rand(10,20);
        vector<int>p;
        for(int i=1;i<=n;i++) p.pb(i);
        random_shuffle(all(p));
        vector<ii>edges;
        for(int i=0;i<n-1;i++){
            edges.pb(ii(p[i],p[i+1]));
        }
        edges.pb(p[n-1],p[0]);
        int m=Rand(n+1,n*n);
        while(edges.size()<m){
            int u=Rand(1,n);
            int v=Rand(1,n);
            while(u!=v) v=Rand(1,n);
            edges.pb(ii(u,v));
        }
        cout<<n<<" "<<m<<'\n';
        for(auto [u,v]:edges){
            cout<<u<<" "<<v<<'\n';
        }
    }
}
