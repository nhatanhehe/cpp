#include    <bits/stdc++.h>
#define fo(i,a,b) for(int i=(a);i<=(b);++i)
#define __unique(V) (V).resize(unique((V).begin(),(V).end())-(V).begin())
#define cntbit(X)   __builtin_popcount((X))
#define bit(S,i) (((S)>>(i))&1)
#define PI	acos(-1)
#define fi  first
#define se  second
#define LL  long long
#define ii  pair<int,int>
#define iii pair<int,ii>
#define eb  emplace_back
#define TASK "countk"
using namespace std;
const int maxn = 1e5 + 5;
int k,m,n,mod,w[maxn];
bool pr[maxn];
///--------------------------
void    readf(){
    cin >> k >> m >> n >> mod;
}
///--------------------------
void	sieve(){
    memset(pr,1,sizeof(pr));
    pr[1] = pr[0] = 0;
    for(int i = 2; i * i < maxn; ++i)
		if (pr[i]) for(int j = i * i; j < maxn; j += i) pr[j] = 0;
}
///--------------------------
void	build(int N,int t){
    for(int i = 2 ; i <= N; ++i) if (pr[i]){
		int tmp = N;
		while (tmp > 0) w[i] += t * (tmp/=i);
    }
}
///--------------------------
int	pw(int a,int b){
    int tmp = 1;
    for(  ; b ; a = 1LL * a * a % mod, b >>= 1)
		if (b & 1) tmp = 1LL * tmp * a % mod;
	return tmp;
}
///--------------------------
int	C(int K,int N){
    memset(w,0,sizeof(w));
    build(N,1); build(K,-1); build(N - K,-1);
    int ans = 1;
    for(int i = 2; i <= N; ++i) if (pr[i])
		ans = 1LL * ans * pw(i,w[i]) % mod;
	return ans;
}
///--------------------------
void    solve(){
	if ((k + m + n) % 2 == 1 || k < abs(m) + abs(n)){
		cout << 0 << '\n';
		return;
    }
    int ans = C(k + m - n >> 1, k) * 1LL * C(k - m - n >> 1,k) % mod;
    cout << ans << '\n';
}
///--------------------------
int     main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    #ifdef TLH2203
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    #endif // TLH2203
    sieve();
    int T;
    cin >> T;
    while (T--){
		readf();
		solve();
    }
}




Viết cho Nguyễn Tiến Nhân

