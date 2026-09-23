#include<bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    vector<int> pref(n, 0), suff(n, 0);
    int open = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') open++;
        pref[i] = open;
    }
    
    int close = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == ')') close++;
        suff[i] = close;
    }
    int min_C = n + 1;
    int best_x = -1;

    for (int x = -1; x < n; x++) {
        int left_open = (x >= 0) ? pref[x] : 0;
        int right_close = (x + 1 < n) ? suff[x + 1] : 0;
        if (left_open + right_close < min_C) {
            min_C = left_open + right_close;
            best_x = x;
        }
    }
    vector<int> mvc;
    for (int i = 0; i <= best_x; i++) {
        if (s[i] == '(') mvc.push_back(i);
    }
    for (int i = best_x + 1; i < n; i++) {
        if (s[i] == ')') mvc.push_back(i);
    }
    int to_remove = min(k, (int)mvc.size());
    string ans(n, '0');
    for (int i = 0; i < to_remove; i++) {
        ans[mvc[i]] = '1';
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}