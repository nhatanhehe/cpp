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
const int mod = 1e9 + 7, moi = 5e5 + 9;
const ll INF = 1e18;
const ld EFS = 1e-12;
const int dx[] = { 1, -1, 0, 0};
const int dy[] = { 0, 0, 1, -1};

struct BIT{
    vector<int> t;
    int n;

    void init(int _n) {
        n = _n;
        t.assign(n + 9, 0);
    }

    void update(int u, int v) {
        for(; u <= n; u += u &-u) {
            t[u] += v;
        }
    }

    int get(int u) {
        int ans = 0;

        for(; u > 0; u -= u &-u) {
            ans += t[u];
        }

        return ans;
    }
};

int n, k, a[moi], cnt = 0, ans = 0, pre[moi], suf[moi];
vector<int> vec, ups;
map<int, int> mp;
BIT t;

void nen() {
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());

    cnt = 0;

    for(int x : vec) {
        mp[x] = ++cnt;
    }
}

void dnc(int l, int r) {
    if(l == r) {
        ans += (a[l] * 3 <= k);
        return;
    }

    int mid = (l + r) / 2;
    dnc(l, mid);
    dnc(mid + 1, r);

    pre[mid + 1] = INF;

    for(int i = mid; i >= l; i--) {
        pre[i] = min(pre[i + 1], a[i]);
    }

    suf[mid] = INF;

    for(int i = mid + 1; i <= r; i++) {
        suf[i] = min(suf[i - 1], a[i]);
    }

    int j = mid + 1;

    for(int i = mid; i >= l; i--) {
        while(j <= r && pre[i] <= suf[j]) {
            ups.push_back(mp[a[j]]);
            t.update(mp[a[j++]], 1);
        }


        int s = k - pre[i] - a[i];
        if(s < 0) continue;
        int pos = upper_bound(vec.begin(), vec.end(), s) - vec.begin() - 1;
        ans += t.get(mp[vec[pos]]);
    }

    for(int x : ups) t.update(x, -1);
    ups.clear();

    j = mid;
    for(int i = mid + 1; i <= r; i++) {
        while(j >= l && suf[i] < pre[j]) {
            ups.push_back(mp[a[j]]);
            t.update(mp[a[j--]], 1);
        }

        int s = k - suf[i] - a[i];
        if(s < 0) continue;
        int pos = upper_bound(vec.begin(), vec.end(), s) - vec.begin() - 1;
        ans += t.get(mp[vec[pos]]);
    }

    for(int x : ups) t.update(x, -1);
    ups.clear();
}

void Input() {
    cin >> n >> k;

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        vec.push_back(a[i]);
    }

    nen();
    t.init(cnt);

    dnc(1, n);
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
