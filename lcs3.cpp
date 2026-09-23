#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
int dp[N][N], a[N], n, m;
map<int, vector<int>> nxt;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= m; i++)
    {
        int x;
        cin >> x;
        nxt[x].push_back(i);
    }

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = 1e9;

    dp[0][0] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            dp[i][j] = dp[i-1][j];
            if (j > 0 && dp[i-1][j-1] != 1e9)
            {
                auto it = upper_bound(nxt[a[i]].begin(), nxt[a[i]].end(), dp[i-1][j-1]);
                if (it != nxt[a[i]].end()) dp[i][j] = min(dp[i][j], *it);
            }
        }
    }

    for (int len = n; len >= 0; len--)
    {
        if (dp[n][len] != 1e9)
        {
            cout << len;
            return 0;
        }
    }


}
