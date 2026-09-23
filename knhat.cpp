#include<bits/stdc++.h>
#define int long long
#define ii pair<int,int>
#define fi first
#define se second
#define task "main"
using namespace std;

const int N = 8e3 + 5, mod = 1e9 + 7;
const int oo = 1e18;
int n, k, t, a[N], ans, pre[4][N];

int tinh(int j, int l, int r)
{
    if(l > r) return 0;
    return pre[j][r] - pre[j][l - 1];
}
main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if(fopen(task ".inp", "r"))
    {
        freopen(task ".inp", "r", stdin);
        freopen(task ".out", "w", stdout);
    }
    cin >> n >> k >> t;
    for(int i = 1; i <= n; i++)
    {
        char c; cin >> c;
        a[i] = c - '0';
        pre[1][i] = pre[1][i - 1] + (a[i] == 1);
        pre[2][i] = pre[2][i - 1] + (a[i] == 2);
        pre[3][i] = pre[3][i - 1] + (a[i] == 3);
    }
    ans = -oo;

    if(pre[1][n] <= k)
    {
        int x = pre[1][n] + pre[2][n] - k;
        x = max(x, 0ll);
        ans = max(ans, n - x);
    }

    if(pre[1][n] + pre[2][n] <= k)
        ans = max(ans, n);

    t++;
    int sum = pre[3][n] + pre[2][n];
    for(int i = t; i <= n; i++)
    {
        for(int j = i; j + t <= n + 1; j++)
        {
            // cout << i << ' ' << j << ' ';
            // cout << tinh(1, 1, i - 1) + tinh(1, j + 1, n) + tinh(2, 1, i - 1) + tinh(2, j + 1, n) << ' ';
            if((tinh(1, 1, i - 1) + tinh(1, j + 1, n) + tinh(2, 1, i - 1) + tinh(2, j + 1, n)) <= k)
            {
                ans = max(ans, tinh(3, 1, i - t) + tinh(3, j + t, n) + tinh(2, 1, i - t) + tinh(2, j + t, n) + tinh(1, 1, i - t) + tinh(1, j + t, n));
            }
            else
            {
                int thieu = tinh(1, 1, i - 1) + tinh(1, j + 1, n) + tinh(2, 1, i - 1)
                    ans = max(ans, tinh(3, 1, i - t) + tinh(3, j + t, n) + tinh(2, 1, i - t) + tinh(2, j + t, n) + tinh(1, 1, i - t) + tinh(1, j + t, n) - thieu);
            }
        }
    }
    if(ans == -oo) cout << -1;
    else
        cout << ans;
}

