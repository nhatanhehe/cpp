#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    int S = 1 << n;
    vector<vector<int>> trans(S);

    // generate transitions: from mask -> possible nextmask
    for (int mask = 0; mask < S; ++mask) {
        // dfs to fill current column
        function<void(int,int)> dfs = [&](int pos, int nextmask) {
            if (pos == n) {
                trans[mask].push_back(nextmask);
                return;
            }
            if (mask & (1 << pos)) {
                // this cell already occupied from left, skip
                dfs(pos + 1, nextmask);
            } else {
                // try place horizontal domino (goes to next column) -> set bit in nextmask
                dfs(pos + 1, nextmask | (1 << pos));
                // try place vertical domino inside this column (cover pos and pos+1)
                if (pos + 1 < n && !(mask & (1 << (pos + 1)))) {
                    dfs(pos + 2, nextmask);
                }
            }
        };
        dfs(0, 0);
    }

    vector<ll> dp(S, 0), ndp(S, 0);
    dp[0] = 1;
    for (int col = 0; col < m; ++col) {
        fill(ndp.begin(), ndp.end(), 0);
        for (int mask = 0; mask < S; ++mask) {
            if (dp[mask] == 0) continue;
            ll ways = dp[mask];
            for (int nm : trans[mask]) {
                ndp[nm] += ways;
                if (ndp[nm] >= MOD) ndp[nm] -= MOD;
            }
        }
        dp.swap(ndp);
    }

    cout << dp[0] % MOD << '\n';
    return 0;
}
