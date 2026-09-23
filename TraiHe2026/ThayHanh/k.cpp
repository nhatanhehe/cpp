#include <bits/stdc++.h>
#define task "ducvodichworldcup"
#define __Thien_dep_trai__ signed main()
#define ll long long
#define ii std::pair<int, int>
#define iii std::pair<ii, int>
#define pll std::pair<ll, ll>
#define vi std::vector<int>
#define vii std::vector<ii>
#define fi first
#define se second
#define pb push_back
#define ins insert
#define sz(x) ((int)(x).size())
#define TIME (1.0 * clock() / CLOCKS_PER_SEC)
#define bit_set(x, pos) ((x) |= (1ULL << (pos)))
#define bit_clear(x, pos) ((x) &= ~(1ULL << (pos)))
#define all(x) x.begin(), x.end()

const int maxn = 1e3;
const ll INF = 1e18;
const int inf = 1e9;
const int mod = 1e9 + 7;
const int inv = (mod + 1) / 2;
const int lg = 20;
const int dx[] = {0, 1, 0, -1, -1, -1, 1, 1};
const int dy[] = {1, 0, -1, 0, -1, 1, -1, 1};

const ll lim = 9e18;

ll add(ll a, ll b)
{
    if (lim - a <= b)
    {
        return lim;
    }
    return a + b;
}

ll mul(ll a, ll b)
{
    if (a == 0)
    {
        return 0;
    }
    if (b == 0)
    {
        return 0;
    }
    if (lim / a <= b)
    {
        return lim;
    }
    return a * b;
}
ll power(ll x, ll y)
{
    if (y == 0)
    {
        return 1;
    }
    ll tmp = power(x, y / 2);
    if (y % 2 == 0)
    {
        return (tmp * tmp) % mod;
    }
    else
    {
        return tmp * tmp % mod * x % mod;
    }
}

std::vector<int> adj[maxn + 7];
char a[maxn + 7][maxn + 7];
ll dp[maxn + 7][maxn + 7], cnt[maxn + 7][maxn + 7];

void solve()
{
    int theta;
    std::cin >> theta;
    int m, n, q;
    std::cin >> m >> n >> q;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            std::cin >> a[i][j];
        }
    }

    if (theta == 3)
    {
        while (q--)
        {
            for (int i = 1; i <= m + n - 1; i++)
            {
                std::cout << a[1][1];
            }
std::cout << "\n";
        }
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dp[i][j] = 0;
        }
    }

    dp[m][n] = 1;
    for (int i = m; i >= 1; i--)
    {
        for (int j = n; j >= 1; j--)
        {
            if (i == m && j == n)
            {
                continue;
            }
            dp[i][j] = add(dp[i + 1][j], dp[i][j + 1]);
        }
    }

    while (q--)
    {
        ll k;
        std::cin >> k;
        std::string res = "";
        res += a[1][1];

        vii vec;
        vec.pb({1, 1});

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cnt[i][j] = 0;
            }
        }
        cnt[1][1] = 1;

        for (int d = 2; d <= m + n - 1; d++)
        {
            vii nxt;
            for (int i = 0; i < sz(vec); i++)
            {
                int r = vec[i].fi;
                int c = vec[i].se;
                ll w = cnt[r][c];

                if (r + 1 <= m)
                {
                    if (cnt[r + 1][c] == 0)
                    {
                        nxt.pb({r + 1, c});
                    }
                    cnt[r + 1][c] = add(cnt[r + 1][c], w);
                }
                if (c + 1 <= n)
                {
                    if (cnt[r][c + 1] == 0)
                    {
                        nxt.pb({r, c + 1});
                    }
                    cnt[r][c + 1] = add(cnt[r][c + 1], w);
                }
            }

            for (char ch = 'a'; ch <= 'z'; ch++)
            {
                ll sum = 0;
for (int i = 0; i < sz(nxt); i++)
                {
                    int r = nxt[i].fi;
                    int c = nxt[i].se;
                    if (a[r][c] == ch)
                    {
                        sum = add(sum, mul(cnt[r][c], dp[r][c]));
                    }
                }

                if (k <= sum)
                {
                    res += ch;
                    vec.clear();
                    for (int i = 0; i < sz(nxt); i++)
                    {
                        int r = nxt[i].fi;
                        int c = nxt[i].se;
                        if (a[r][c] == ch)
                        {
                            vec.pb({r, c});
                        }
                    }
                    break;
                }
                else
                {
                    k -= sum;
                }
            }
        }
        std::cout << res << "\n";
    }
}

__Thien_dep_trai__
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    if (std::fopen(task ".inp", "r"))
    {
        std::freopen(task ".inp", "r", stdin);
        std::freopen(task ".out", "w", stdout);
    }

    int tt = 1;
    // std::cin >> tt;
    while (tt--)
    {
        solve();
    }

    std::cerr << "\nTime elapsed: " << TIME << " s.\n";

    return 0;
}

