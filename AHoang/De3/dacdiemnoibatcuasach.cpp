#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define ii pair<int,int>
#define iii tuple<int,int,int>
#define all(x) x.begin(), x.end()
#define mems(x,y) memset(x, y, sizeof(x))
#define debug(x) cout << #x << " = " << x << '\n'
#define Task "a"

const int mod = 1e9 + 7;
const ll INF = 1e18;

int n, m, q;

struct BIT {
    vector<int> t;
    int n;

    void init(int _n) {
        n = _n;
        t.assign(n + 5, 0);
    }

    void update(int u, int v) {
        for (; u <= n; u += u & -u)
            t[u] += v;
    }

    int get(int u) {
        ll ans = 0;
        for (; u > 0; u -= u & -u)
            ans += t[u];
        return ans;
    }

    void update(int l, int r, int v) {
        update(l, v);
        update(r + 1, -v);
    }
};

BIT T;

bool cmp(const iii &A, const iii &B) {
    auto [l1, r1, t1] = A;
    auto [l2, r2, t2] = B;

    if (l1 != l2) return l1 < l2;
    if (t1 != t2) return t1 < t2;
    return r1 < r2;
}

vector<ll> ans;
vector<vector<int>> v, spe;
vector<vector<iii>> question;

void Input() {
    cin >> n >> m;

    v.assign(n + 5, {});
    spe.assign(m + 5, {});
    question.assign(m + 5, {});
    ans.assign(500000 + 5, 0);

    for (int i = 1; i <= m; i++)
        spe[i].pb(0);

    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        while (k--) {
            int x;
            cin >> x;
            v[i].pb(x);
            spe[x].pb(i);
        }
    }

    for (int i = 1; i <= m; i++)
        spe[i].pb(n + 1);

    cin >> q;

    for (int i = 1; i <= q; i++) {
        int l, r, p;
        cin >> l >> r >> p;
        question[p].pb({l, r, i});
    }

    T.init(n);

    for (int i = 1; i <= n; i++) {
        vector<iii> qu;

        for (int x : v[i]) {
            int r = upper_bound(all(spe[x]), i) - spe[x].begin();
            int l = lower_bound(all(spe[x]), i) - spe[x].begin() - 1;

            qu.pb({spe[x][l] + 1, spe[x][r] - 1, -1000000000});
            qu.pb({spe[x][r], spe[x][l] + 1, -200000000});
        }

        for (auto &[l, r, id] : question[i])
            qu.pb({r, l, id});

        sort(all(qu), cmp);

        for (auto [l, r, id] : qu) {
            if (id == -1000000000) {
                T.update(l, r, 1);
            }
            else if (id == -200000000) {
                swap(l, r);
                T.update(l, r - 1, -1);
            }
            else {
                swap(l, r);
                ans[id] = T.get(l);
            }
        }
    }

    for (int i = 1; i <= q; i++)
        cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (fopen(Task ".inp", "r")) {
        freopen(Task ".inp", "r", stdin);
        freopen(Task ".out", "w", stdout);
    }

    int tc = 1;
    //cin >> tc;
    while (tc--)
        Input();

    cerr << "Time: " << fixed << setprecision(9) << 1.0 * clock() / CLOCKS_PER_SEC << " s\n";
}
