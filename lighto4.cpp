#include <bits/stdc++.h>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define int long long
#define fi first
#define se second

#define V "3f3f3f3f3f3f3f3f"

using namespace std;

const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
const int LOG = 20;

int n, m, cur = 0, d[N];
long long ans = 0;
vector<int> adj[N];

struct node {
    int l, r, id;
    long long cnt;
} q[N];

struct tri {
    long long c[LOG][2];
} x[N];

struct val {
    long long cnt;
    int l, r;
} f[N];

void solve() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                adj[id[cur++] = i].push_back(j);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        s[i] = {adj[id[x].se].se};
    }

    for (int i = 1; i <= n; i++) {
        for (int len = 1; len <= i; len++) {
            l[i][len] = l[i - 1][len] << 1;
            len[i][0] = 0;
            for (int j = 1; j <= i; j++) {
                r[i][j] = (r[i][j - 1] << 1);
                adj[i][j] = adj[i][j - 1] << 1;
                c[i][j] = (c[i][j - 1] << 1);
                c[i][j][0] = (c[i][j - 1][0] << 1);
            }
        }
    }

    for (int i = n; i >= 1; i--) {
        for (int j = i; j <= n; j++) {
            d[i][j] = (d[i][j + 1] << 1);
            d[i][j][0] = (d[i][j + 1][0] << 1);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int l = 1; l < n; l++) {
                if (i + l > n) continue;
                if (l + j > n) continue;
                x[l][i] = x[l - 1][i] ^ x[l - 1][i + 1];
                ans += (x[l][i].l & f[l][i].r) ^ (f[l][i + 1].l & x[l][i].r);
                ans += len[i - 1][l] & (x[l][i].f2.se & f[l][i + 1].f3.l & x[l][i].f3.se & d[l][i].f1.l & x[l][i].se);
            }
        }
    }

    cout << ans;
}

main() {
    solve();
}
