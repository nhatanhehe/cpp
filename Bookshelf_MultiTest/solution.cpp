#include <bits/stdc++.h>
using namespace std;

#define int long long

const long long inf = 1e18;
const int N = 2e5 + 5;

int w[N], h[N], dp[N];

struct SegmentTree {
    vector<long long> tree, lz;
    int n;

    void init(int _n) {
        n = _n;
        // Use assign to properly reset memory for each testcase
        tree.assign(n * 4 + 10, 0);
        lz.assign(n * 4 + 10, 0);
    }

    void apply(int id, long long k) {
        tree[id] += k;
        lz[id] += k;
    }

    void push(int id) {
        if (lz[id]) {
            apply(id * 2, lz[id]);
            apply(id * 2 + 1, lz[id]);
            lz[id] = 0;
        }
    }

    void up(int u, int v, long long k, int id = 1, int l = 0, int r = -1) {
        if (r == -1) r = n;
        if (l > v || r < u) return;
        if (u <= l && r <= v) {
            apply(id, k);
            return;
        }
        push(id);
        int mid = (l + r) >> 1;
        up(u, v, k, id * 2, l, mid);
        up(u, v, k, id * 2 + 1, mid + 1, r);
        tree[id] = min(tree[id * 2], tree[id * 2 + 1]);
    }

    long long get(int u, int v, int id = 1, int l = 0, int r = -1) {
        if (r == -1) r = n;
        if (l > v || r < u) return inf;
        if (u <= l && r <= v) return tree[id];
        push(id);
        int mid = (l + r) >> 1;
        return min(get(u, v, id * 2, l, mid), get(u, v, id * 2 + 1, mid + 1, r));
    }
};

void solve() {
    int n, l;
    // Read until EOF
    while (cin >> n >> l) {
        SegmentTree seg;
        seg.init(n);

        h[0] = 1e9 + 3;
        for (int i = 1; i <= n; i++) {
            cin >> h[i] >> w[i];
        }

        deque<int> dq = {0};
        long long j = 1, sum = 0;

        for (int i = 1; i <= n; i++) {
            sum += w[i];

            while (h[dq.back()] <= h[i]) {
                seg.up(dq[dq.size() - 2], dq.back() - 1, -h[dq.back()]);
                dq.pop_back();
            }
            seg.up(dq.back(), i - 1, h[i]);

            while (sum > l) {
                sum -= w[j++];
            }

            dp[i] = seg.get(j - 1, i - 1);
            seg.up(i, i, dp[i]);
            dq.push_back(i);
        }

        cout << dp[n] << "\n";
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}