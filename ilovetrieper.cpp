#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const int LOG_W = 30;
const int LOG_N = 20;

struct Node {
    int count;
    int child[2];
} trie[MAXN * LOG_W + MAXN * 2];

int trie_cnt = 0;
int roots[MAXN];

int up[MAXN][LOG_N];
int depth[MAXN];

int update(int prev_node, int val, int bit) {
    int cur = ++trie_cnt;
    trie[cur] = trie[prev_node];
    trie[cur].count++;

    if (bit < 0) return cur;

    int b = (val >> bit) & 1;
    trie[cur].child[b] = update(trie[prev_node].child[b], val, bit - 1);

    return cur;
}

int get_cnt(int u, int c) {
    return trie[trie[u].child[c]].count;
}

// --- PHẦN THAY ĐỔI CHÍNH Ở ĐÂY ---
// Tìm số NHỎ thứ k
int query(int u, int v, int lca, int plca, int k, int bit) {
    if (bit < 0) return 0;

    // Đếm số lượng phần tử bên nhánh trái (bit 0)
    int cnt_left = get_cnt(u, 0) + get_cnt(v, 0) - get_cnt(lca, 0) - get_cnt(plca, 0);

    if (k <= cnt_left) {
        // Tìm trong nhánh trái (bit 0)
        return query(trie[u].child[0], trie[v].child[0], trie[lca].child[0], trie[plca].child[0], k, bit - 1);
    } else {
        // Tìm trong nhánh phải (bit 1) -> Kết quả chắc chắn có bit này là 1
        return (1 << bit) + query(trie[u].child[1], trie[v].child[1], trie[lca].child[1], trie[plca].child[1], k - cnt_left, bit - 1);
    }
}
// ---------------------------------

void add_node(int p, int id, int w) {
    depth[id] = depth[p] + 1;
    up[id][0] = p;
    for (int i = 1; i < LOG_N; i++) {
        up[id][i] = up[up[id][i-1]][i-1];
    }

    roots[id] = update(roots[p], w, LOG_W - 1);
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    for (int i = LOG_N - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }

    if (u == v) return u;

    for (int i = LOG_N - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, Q, r, w;
    if (!(cin >> n >> Q >> r >> w)) return 0;

    roots[0] = 0;
    trie[0].count = 0; trie[0].child[0] = trie[0].child[1] = 0;

    depth[r] = 1;
    for(int i=0; i<LOG_N; i++) up[r][i] = 0;
    roots[r] = update(roots[0], w, LOG_W - 1);

    while (Q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int p, id, weight;
            cin >> p >> id >> weight;
            add_node(p, id, weight);
        } else {
            int u, v, k;
            cin >> u >> v >> k;
            int lca = get_lca(u, v);
            int par_lca = up[lca][0];

            cout << query(roots[u], roots[v], roots[lca], roots[par_lca], k, LOG_W - 1) << "\n";
        }
    }

    return 0;
}
