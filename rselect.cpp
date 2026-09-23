#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define debug(x) cout<< #x << " = "<< x <<'\n'
#define Task ""
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

const int Q = 1e3 + 69;
int n, a[Q][Q], ans = 1, vis[Q][Q], timer = 0;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int bfs(int x, int y, int d) {
    queue<iii> qu;
    qu.push({x, {y, d}});
    timer++;
    vis[x][y] = timer;
    int cnt = 1;
    while (!qu.empty()) {
        iii top = qu.front();
        int cx = top.fi, cy = top.se.fi, cd = top.se.se;
        qu.pop();
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i], ny = cy + dy[i];
            if (1 <= nx && nx <= n && 1 <= ny && ny <= n && vis[nx][ny] != timer && abs(a[nx][ny] - a[cx][cy]) == cd) {
                qu.push({nx, {ny, cd}});
                vis[nx][ny] = timer;
                cnt++;
            }
        }
    }
    return cnt;
}

void solve() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            for (int k = 0; k < 4; k++) {
                int cx = i + dx[k];
                int cy = j + dy[k];
                if (1 <= cx && cx <= n && 1 <= cy && cy <= n && vis[cx][cy] == 0) {
                    ans = max(ans, bfs(cx, cy, abs(a[cx][cy] - a[i][j])));
                }
            }
        }
    cout << ans << "\n";
}

main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }

    if (cin >> n) {
        solve();
    }
}
