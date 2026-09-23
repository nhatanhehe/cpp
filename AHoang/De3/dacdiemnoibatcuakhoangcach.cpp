#include <bits/stdc++.h>
#define task "a"
#define ll long long
#define ld long double
#define iii tuple<int, int, int>
#define ii pair<int, int>
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define mems(x, y) memset(x, y, sizeof(x));
using namespace std;
const int mod = 1e9 + 7, moi = 5e5 + 9;
const ll INF = 1e18;
const ld EFS = 1e-12;
const int dx[] = { 1, -1, 0, 0};
const int dy[] = { 0, 0, 1, -1};

struct BIT {
    vector<int> t;
    int n;

    void init(int _n) {
        n = _n;
        t.resize(n + 9);
    }

    void update(int u, int v) {
        for(; u <= n; u += u&-u) {
            t[u] += v;
        }
    }

    int get(int u) {
        ll ans = 0;

        for(; u > 0; u -= u&-u) {
            ans += t[u];
        }

        return ans;
    }

    void update(int l, int r, int v) {
        update(l, v);
        update(r + 1, -v);
    }
};

int n, m, q;
ll ans[moi];
vector<int> v[moi], spe[moi];
vector<iii> question[moi];
BIT t;

bool cmp(iii x, iii y) {

    auto [lx, rx, tx] = x;
    auto [ly, ry, ty] = y;

    if(lx != ly) return lx < ly;
    if(tx != ty) return tx < ty;
    return rx < ry;
}

vector<iii> b;

void Input() {
    cin >> n >> m;

    for(int i = 1; i <= m; i++) spe[i].push_back(0);

    for(int i = 1; i <= n; i++) {
        int k;
        cin >> k;

        for(int j = 1; j <= k; j++) {
            int x;
            cin >> x;

            v[i].push_back(x);
            spe[x].push_back(i);
        }
    }

    for(int i = 1; i <= m; i++) spe[i].push_back(n + 1);

    cin >> q;

    for(int i = 1; i <= q; i++) {
        int l, r, p;
        cin >> l >> r >> p;

        question[p].push_back({l, r, i});
    }

    t.init(n);

    for(int i = 1; i <= n; i++) {

        vector<iii> qu;

        for(int x : v[i]) {
            int r = upper_bound(all(spe[x]), i) - spe[x].begin();
            int l = lower_bound(all(spe[x]), i) - spe[x].begin() - 1;

            //cout << i << " " << x << " " << spe[x][l] + 1 << " " << spe[x][r] - 1 << '\n';

            qu.push_back({spe[x][l] + 1, spe[x][r] - 1, -1e9});
            qu.push_back({spe[x][r], spe[x][l] + 1, -1e8});
        }


        for(auto [l, r, id] : question[i]) {
            qu.push_back({r, l, id});
        }

        sort(all(qu), cmp);

        for(auto [l, r, tt] : qu) {
            if(tt == -1e9) {
                t.update(l, r, 1);
                continue;
            }

            else if(tt == -1e8) {
                swap(l, r);
                t.update(l, r - 1, -1);
                continue;
            }

            else {
                swap(l, r);
                ans[tt] = t.get(l);
            }
        }
    }

    for(int i = 1; i <= q; i++) {
        cout << ans[i] << '\n';
    }
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




