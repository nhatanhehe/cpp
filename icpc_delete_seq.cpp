#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
    struct Node {
        map<char, int> next;
        int fail;
        vector<int> output;
        int output_link;
    };
    vector<Node> nodes;

    AhoCorasick() {
        nodes.push_back(Node());
    }

    void add_pattern(const string &s, int id) {
        int cur = 0;
        for (char c : s) {
            if (nodes[cur].next.count(c) == 0) {
                nodes[cur].next[c] = nodes.size();
                nodes.push_back(Node());
            }
            cur = nodes[cur].next[c];
        }
        nodes[cur].output.push_back(id);
    }

    void build() {
        queue<int> q;
        nodes[0].fail = 0;
        nodes[0].output_link = -1;
        for (auto &p : nodes[0].next) {
            int v = p.second;
            nodes[v].fail = 0;
            nodes[v].output_link = -1;
            q.push(v);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &p : nodes[u].next) {
                char c = p.first;
                int v = p.second;
                int f = nodes[u].fail;
                while (f != 0 && nodes[f].next.count(c) == 0) {
                    f = nodes[f].fail;
                }
                if (nodes[f].next.count(c)) {
                    f = nodes[f].next[c];
                }
                nodes[v].fail = f;
                if (nodes[f].output.size() > 0) {
                    nodes[v].output_link = f;
                } else {
                    nodes[v].output_link = nodes[f].output_link;
                }
                q.push(v);
            }
        }
    }

    vector<tuple<int, int, long long>> traverse(const string &T, const vector<int> &pat_len, const vector<long long> &pat_val) {
        vector<tuple<int, int, long long>> occurrences;
        int state = 0;
        int n = T.size();
        for (int i = 0; i < n; i++) {
            char c = T[i];
            while (state != 0 && nodes[state].next.count(c) == 0) {
                state = nodes[state].fail;
            }
            if (nodes[state].next.count(c)) {
                state = nodes[state].next[c];
            } else {
                state = 0;
            }
            for (int v = state; v != -1; v = nodes[v].output_link) {
                for (int id : nodes[v].output) {
                    int len = pat_len[id];
                    int start = i - len + 2;
                    int end = i + 1;
                    occurrences.push_back({start, end, pat_val[id]});
                }
            }
        }
        return occurrences;
    }
};

struct Fenw {
    int n;
    vector<long long> tree;
    Fenw(int n) : n(n), tree(n + 1, 0) {}
    void update(int i, long long delta) {
        for (; i <= n; i += i & -i) {
            tree[i] += delta;
        }
    }
    long long query(int i) {
        long long s = 0;
        for (; i > 0; i -= i & -i) {
            s += tree[i];
        }
        return s;
    }
    long long range_query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N, Q;
    cin >> N >> Q;
    vector<string> patterns(N);
    vector<long long> c(N);
    for (int i = 0; i < N; i++) {
        cin >> patterns[i] >> c[i];
    }

    string T;
    cin >> T;
    int n = T.size();

    vector<int> pat_len(N);
    for (int i = 0; i < N; i++) {
        pat_len[i] = patterns[i].size();
    }

    AhoCorasick ac;
    for (int i = 0; i < N; i++) {
        ac.add_pattern(patterns[i], i);
    }
    ac.build();

    auto occurrences = ac.traverse(T, pat_len, c);

    sort(occurrences.begin(), occurrences.end(), [](const auto &a, const auto &b) {
        return get<1>(a) < get<1>(b);
    });

    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < Q; i++) {
        int L, R;
        cin >> L >> R;
        queries.push_back({L, R, i});
    }

    sort(queries.begin(), queries.end(), [](const auto &a, const auto &b) {
        return get<1>(a) < get<1>(b);
    });

    Fenw fenw(n);
    vector<long long> ans(Q);
    int j = 0;
    for (auto &q : queries) {
        int L = get<0>(q);
        int R = get<1>(q);
        int idx = get<2>(q);
        while (j < occurrences.size() && get<1>(occurrences[j]) <= R) {
            int s = get<0>(occurrences[j]);
            long long val = get<2>(occurrences[j]);
            fenw.update(s, val);
            j++;
        }
        ans[idx] = fenw.range_query(L, n);
    }

    for (long long a : ans) {
        cout << a << '\n';
    }

    return 0;
}
