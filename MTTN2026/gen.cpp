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
main(){
    srand(time(NULL));
    freopen("a.inp","w", stdout);
    int n=10,s=2000,t=2000;
    cout<<n<<" "<<t<<" "<<s<<'\n';
    for(int i=1;i<=n;i++){
        cout<<Rand(1,10)<<" ";
    }
    cout<<'\n';
    for(int i=1;i<=n;i++){
        cout<<Rand(1,10)<<" ";
    }
    //system("chamthitrau.exe");
    //system("hethongchamthi.exe");
}

