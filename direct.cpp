#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
const int LOG = 20;
const int MOD = 1e9 + 7;

int n, m;
vector<int> g[MAXN];
int up[MAXN][LOG], depth[MAXN];
int high[MAXN];
int color[MAXN];
vector<pair<int,int>> logic[MAXN]; // đồ thị logic (v, parity)

// ========== LCA ==========
void dfs_lca(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i < LOG; i++)
        up[u][i] = up[up[u][i - 1]][i - 1];
    for (int v : g[u]) if (v != p) {
        depth[v] = depth[u] + 1;
        dfs_lca(v, u);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    for (int i = LOG - 1; i >= 0; i--)
        if (diff >> i & 1) a = up[a][i];
    if (a == b) return a;
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}

// ========== Cập nhật ràng buộc ==========
void add_path(int a, int b) {
    int c = lca(a, b);
    high[a]++;
    high[b]++;
    high[c] -= 2;
}

// ========== Duyệt cây, cộng dồn high và tạo đồ thị logic ==========
void connect(int u, int p) {
    for (int v : g[u]) if (v != p) {
        connect(v, u);
        if (high[v] > 0) {
            // Cạnh (u, v) nằm trong ít nhất một đường ràng buộc
            logic[u].push_back({v, 0});
            logic[v].push_back({u, 0});
        }
        high[u] += high[v];
    }
}

// ========== DFS tô màu (0/1) để kiểm tra mâu thuẫn ==========
bool dfs_color(int u, int c) {
    color[u] = c;
    for (auto [v, w] : logic[u]) {
        int nc = c ^ w;
        if (color[v] == -1) {
            if (!dfs_color(v, nc)) return false;
        } else if (color[v] != nc) {
            return false; // mâu thuẫn logic
        }
    }
    return true;
}

// ========== Hàm powmod (2^k % MOD) ==========
long long modpow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    depth[1] = 0;
    dfs_lca(1, 0);

    vector<pair<int,int>> pairs;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        pairs.push_back({a, b});
        add_path(a, b);
    }

    connect(1, 0);

    // Nếu cần, thêm ràng buộc "ngược chiều" (parity = 1)
    // khi cả a và b khác LCA. (Không cần nếu chỉ xét đồng hướng)

    // ========== Tô màu đồ thị logic ==========
    long long ans = 1;
    memset(color, -1, sizeof(color));

    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            if (!dfs_color(i, 0)) {
                cout << 0 << "\n";
                return 0;
            }
            ans = (ans * 2) % MOD; // mỗi thành phần logic có 2 cách
        }
    }

    // ========== Đếm số cạnh tự do ==========
    int free_edges = 0;
    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) if (v > u) { // tránh đếm 2 lần
            // cạnh (u,v) tự do nếu không nằm trong ràng buộc
            if (high[v] == 0 && high[u] == 0)
                free_edges++;
        }
    }

    ans = ans * modpow(2, free_edges) % MOD;

    cout << ans << "\n";
    return 0;
}

