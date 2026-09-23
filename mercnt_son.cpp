#include <bits/stdc++.h>
#define task "a"
#define ll long long
#define ld long double
#define ii pair<int, int>
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define mems(x, y) memset(x, y, sizeof(x));
using namespace std;
const int mod = 1e9 + 7, moi = 7e3 + 9;
const ll INF = 1e18;
const ld EFS = 1e-12;
const int dx[] = { 1, -1, 0, 0};
const int dy[] = { 0, 0, 1, -1};

struct pt {

};

ll add(ll t, ll x) {
    t += x;

    if(t >= mod) t -= mod;
    if(t < 0) t += mod;

    return t;
}

ll n, a[moi], S[moi];
int dp[moi][moi], pre[moi][moi];

void Input() {
    cin >> n;

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    S[0] = 0;
    for(int i = 1; i <= n; i++) {
        S[i] = S[i - 1] + a[i];
    }

    dp[0][0] = 1;
    pre[0][0] = 1;

    for(int i = 1; i <= n; i++) {

        for(int j = i; j >= 1; j--) {

            ll Sum = S[i] - S[j - 1];
            ll Sum2 = 2 * S[j - 1] - Sum;

            ll pos = upper_bound(S + 1, S + n + 1, Sum2) - S - 1;

            dp[i][j] += pre[j - 1][j - 1] - pre[j - 1][pos ];

            //cout << Sum2 << " " << i << " " << j << " " << pos << " " << dp[i][j] << '\n';
        }


        for(int j = 1; j <= i; j++) {
            pre[i][j] += pre[i][j - 1] + dp[i][j];
        }
    }

    cout << pre[n][n];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    if(fopen(task".inp","r")){
        freopen(task".inp","r",stdin);
        freopen(task".out","w",stdout);
    }
    int t = 1;
    //cin >> t;
    while (t --) {
        Input();
    }

    cerr << "Time: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s.\n";
}




