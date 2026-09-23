#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 200000 + 5;

int n;
ll t[N];
vector<int> adj[N];

int parent_[N];
ll compMax[N];
bool active[N];

int find_set(int x) {
    if (parent_[x] == x) return x;
    return parent_[x] = find_set(parent_[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Nếu đề bắt đọc/ghi file thì mở 2 dòng dưới:
    // freopen("GOLD.INP", "r", stdin);
    // freopen("GOLD.OUT", "w", stdout);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> t[i];

    for (int i = 1; i <= n; i++) {
        parent_[i] = i;
        compMax[i] = t[i];
    }

    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> order;
    order.reserve(n);
    for (int i = 1; i <= n; i++) order.push_back(i);

    sort(order.begin(), order.end(), [&](int a, int b) {
        if (t[a] != t[b]) return t[a] < t[b];
        return a < b;
    });

    ll ans = 0;

    for (int v : order) {
        active[v] = true;

        for (int u : adj[v]) {
            if (!active[u]) continue;

            int ru = find_set(u);
            int rv = find_set(v);

            if (ru == rv) continue;

            ans += t[v] + compMax[ru];
            parent_[ru] = rv;
            compMax[rv] = max(compMax[rv], compMax[ru]);
        }
    }

    cout << ans;
    return 0;
}