#include <bits/stdc++.h>
#define task "a"
#define int long long
#define ll long long
#define ld long double
#define ii pair<int, int>
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define mems(x, y) memset(x, y, sizeof(x));
using namespace std;
const int mod = 998244353, moi = 1e2 + 9;
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

ll mul(ll t, ll x) {
    return ((t % mod) * (x % mod)) % mod;
}

ll cal(ll t, ll x) {
    if(x == 0) return 1;

    ll s = cal(t, x / 2);

    s = mul(s, s);
    if(x % 2 != 0) s = mul(s, t);

    return s;
}

ll fac[moi], ifac[moi];

void pre() {
    int Max = 1e2;
    fac[0] = 1;
    for(int i = 1; i <= Max; i++) {
        fac[i] = mul(fac[i - 1], i);
    }

    ifac[Max] = cal(fac[Max], mod - 2);

    for(int i = Max - 1; i >= 0; i--) ifac[i] = mul(ifac[i + 1], i + 1);
}

ll C(int k, int n) {
    if(k < 0 || k > n) return 0;

    return mul(fac[n], mul(ifac[k], ifac[n - k]));
}


int n, S, k, c[moi], v[moi];
ll dp[moi][moi][moi];


void Input() {
    cin >> n >> S >> k;
    pre();
    for(int i = 1; i <= n; i++) {
        cin >> c[i] >> v[i];
    }

    dp[0][0][0] = 1;

    for(int i = 1; i <= n; i++) {

        for(int w = S; w >= 0; w--) {


            for(int p = 0; p <= k; p++) {
                ll &res = dp[i][w][p];
                res = add(res, dp[i - 1][w][p]);

                if(w < c[i]) continue;

                if(p == 0) res = add(res, dp[i - 1][w - c[i]][p]);
                else {
                    for(int q = 0; q <= p; q++) {

                        ll a = dp[i - 1][w - c[i]][p - q];
                        ll b = v[i];
                        ll c = C(q, p);

                        a = mul(a, c);
                        b = cal(b, q);

                        res = add(res, mul(a, b));
                    }
                }
            }
        }
    }

    ll ans = 0;

    for(int i = 0; i <= S; i++) {
        ans = add(ans, dp[n][i][k]);
    }

    cout << ans;
}

main(){
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
