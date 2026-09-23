#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;

int count_blocks() {
    int cnt = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i - 1]) cnt++;
    }
    return cnt;
}

void solve() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> temp = a;
    sort(temp.begin(), temp.end());
    int distinct = unique(temp.begin(), temp.end()) - temp.begin();

    int initial_blocks = count_blocks();
    if (initial_blocks == distinct) {
        cout << "YES\n";
        return;
    }
    if (initial_blocks - distinct > 4) {
        cout << "NO\n";
        return;
    }

    map<int, int> block_cnt;
    int last_val = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] != last_val) {
            block_cnt[a[i]]++;
            last_val = a[i];
        }
    }
    vector<int> cand;
    for (int i = 0; i < n; i++) {
        if (block_cnt[a[i]] > 1) {
            if (i == 0 || a[i] != a[i - 1]) {
                cand.push_back(i);
                if (i > 0) cand.push_back(i - 1);
            }
            if (i == n - 1 || a[i] != a[i + 1]) {
                cand.push_back(i);
                if (i < n - 1) cand.push_back(i + 1);
            }
        }
    }

    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());
    auto get_local = [&](int i, int j) {
        set<int> idx;
        if (i > 0) idx.insert(i - 1);
        if (i < n - 1) idx.insert(i);
        if (j > 0) idx.insert(j - 1);
        if (j < n - 1) idx.insert(j);

        int transitions = 0;
        for (int x : idx) {
            if (a[x] != a[x + 1]) transitions++;
        }
        return transitions;
    };
    for (int i = 0; i < cand.size(); i++) {
        for (int j = i + 1; j < cand.size(); j++) {
            int u = cand[i], v = cand[j];
            int before = get_local(u, v);
            
            swap(a[u], a[v]);
            int after = get_local(u, v);
            swap(a[u], a[v]); 

            if (initial_blocks - before + after == distinct) {
                cout << "YES\n";
                return;
            }
        }
    }

    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}