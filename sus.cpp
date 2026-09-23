#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, C;
    cin >> N >> C;

    vector<pair<ll,ll>> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i].first >> a[i].second; // t_i, d_i
    }

    sort(a.begin(), a.end()); // theo t_i

    ll curTime = 0;
    int i = 0;

    while (i < N) {
        // nếu quầy rảnh mà chưa ai đến
        curTime = max(curTime, a[i].first);

        ll sumD = 0;
        int cnt = 0;

        // lấy tối đa C người đã đến
        while (i < N && cnt < C && a[i].first <= curTime) {
            sumD += a[i].second;
            i++;
            cnt++;
        }

        curTime += sumD;
    }

    cout << curTime;
    return 0;
}

