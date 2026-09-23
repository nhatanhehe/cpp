#include <bits/stdc++.h>
#define task "recruitment"
#define ll long long
#define ld long double
#define ii pair<int, int>
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define mems(x, y) memset(x, y, sizeof(x));
using namespace std;

const ll MOD = 1000000000LL + 19972207LL;
const int moi = 100000 + 9;
const ll INF = (ll)1e18;
const ld EFS = 1e-12;
const int dx[] = { 1, -1, 0, 0 };
const int dy[] = { 0, 0, 1, -1 };

ll modpow(ll a, ll e) {
    ll r = 1 % MOD;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

void Input() {

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    if (fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }

    int T;
    cin >> T;

    vector<ii> qs(T);
    int maxn = 0;
    for (int i = 0; i < T; i++) {
        int n, k;
        cin >> n >> k;
        qs[i] = { n, k };
        maxn = max(maxn, n);
    }

    if (maxn < 1) maxn = 1;

    vector<ll> fact(maxn + 1), invfact(maxn + 1), inv(maxn + 1);
    fact[0] = 1;
    for (int i = 1; i <= maxn; i++) fact[i] = fact[i - 1] * i % MOD;

    inv[1] = 1;
    for (int i = 2; i <= maxn; i++) {
        ll q = MOD / i;
        ll r = MOD % i;
        inv[i] = (MOD - q * inv[r] % MOD) % MOD;
    }

    invfact[maxn] = modpow(fact[maxn], MOD - 2);
    for (int i = maxn; i >= 1; i--) invfact[i - 1] = invfact[i] * i % MOD;

    for (auto &p : qs) {

        int n = p.fi, k = p.se;
        if (n <= 1) {
            cout << 0 << '\n';
            continue;
        }

        vector<ll> a(n);
        a[0] = 1;

        for (int i = 1; i <= n - 1; i++) {
            ll s = 0;
            int L = max(0, i - k);
            for (int j = L; j <= i - 1; ++j) {
                s += a[j];
                if (s >= MOD) s -= MOD;
            }
            a[i] = s * inv[i] % MOD;
        }

        ll S = 0, res = 0;

        for (int t = 0; t <= n - 1; t++) {
            S += a[t];
            if (S >= MOD) S -= MOD;
            res += S * invfact[n - 1 - t] % MOD;
            if (res >= MOD) res -= MOD;
        }

        ll sel = fact[n - 1] * res % MOD;

        ll tot_sum = 0;

        for (int m = 0; m <= n - 1; m++) {
            ll val = (ll)(n - m) * invfact[m] % MOD;
            tot_sum += val;
            if (tot_sum >= MOD) tot_sum -= MOD;
        }

        ll tot = fact[n - 1] * tot_sum % MOD;

        ll ans = (tot + MOD - sel) % MOD;
        cout << ans << '\n';
    }

    cerr << "Time: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s.\n";
    return 0;
}
