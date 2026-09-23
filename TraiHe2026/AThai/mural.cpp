#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define pb push_back
#define all(x) x.begin(),x.end()
#define fi first
#define se second

const ll N = 4e5 + 5;

int n;
int a[N], b[N];
int pa[N], pb[N];
ll cnt[N * 4];
main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    if (fopen("a.inp", "r")) {
        freopen("a.inp", "r", stdin);
        freopen("a.out", "w", stdout);
    }

    cin>>n;

    vector<int> cp;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        if(i>=2) pa[i] = max(pa[i - 1], a[i]);

        cp.pb(a[i]);
        if(i >= 2) cp.pb(pa[i]);
    }
    pa[1]=a[1];
    for(int i = 1; i <= n; i++){
        cin >> b[i];
        if(i>=2) pb[i] = max(pb[i - 1], b[i]);

        cp.pb(b[i]);
        if(i >= 2) cp.pb(pb[i]);
    }
    pb[1]=b[1];
    sort(all(cp));
    cp.erase(unique(all(cp)), cp.end());
    auto get_id = [&](int val) {
        return lower_bound(all(cp), val) - cp.begin() + 1;
    };

    cnt[get_id(a[1])]++;
    for(int i = 2; i <= n; i++){
        cnt[get_id(a[i])]++;
        cnt[get_id(b[i])]++;
    }
    for(int i = 2; i <= n; i++){
        int x = upper_bound(pa + 2, pa + n + 1, pb[i]) - (pa + 2);
        cnt[get_id(pb[i])] += x;
        int y = lower_bound(pb + 2, pb + n + 1, pa[i]) - (pb + 2);
        cnt[get_id(pa[i])] += y;
    }
    ll max_count = 0;
    int best_val = 0;

    for(int i = 1; i <= cp.size(); i++){
        int current_val = cp[i - 1];
        if (cnt[i] > max_count) {
            max_count = cnt[i];
            best_val = current_val;
        } else if (cnt[i] == max_count && current_val > best_val) {
            best_val = current_val;
        }
    }

    cout << best_val << " " << max_count << '\n';

    return 0;
}
