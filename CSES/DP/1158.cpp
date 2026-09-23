#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define all(x) x.begin(), x.end()
const ll inf = 1e18;
const ll mod = 1e9 + 7;
const ll N = 2e5 + 5;
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, x;
    cin >> n >> x;
    vector<int> h(n), s(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    for (int i = 0; i < n; i++) cin >> s[i];
    vector<int> dp(x + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int j = x; j >= h[i]; j--) {
            dp[j] = max(dp[j], dp[j - h[i]] + s[i]);
        }
    }

    int ans = 0;
    for (int j = 0; j <= x; j++) ans = max(ans, dp[j]);
    cout << ans << "\n";

    return 0;
}

