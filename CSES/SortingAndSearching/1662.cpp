#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<long long> cnt(n, 0);
    long long prefix = 0;
    cnt[0] = 1; // prefix sum = 0

    for (int i = 0; i < n; i++) {
        prefix += a[i];
        int mod = ((prefix % n) + n) % n; // handle negative
        cnt[mod]++;
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += cnt[i] * (cnt[i] - 1) / 2;
    }

    cout << ans;
}
