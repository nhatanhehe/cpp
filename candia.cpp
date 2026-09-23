#include<bits/stdc++.h>
using namespace std;

#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << '\n'
#define Task "twosum"
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(), x.end()
#define fi first
#define se second
const int N=1e6+6;
const ll inf = 1e18;
ll n,a[N];
main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    ll Target;
    cin >> n>> Target;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int l = 1, r = n;
    while (l < r) {
        ll sum = a[l] + a[r];
        if (sum == Target) {
            while (r - 1 > l && a[l] + a[r - 1] == Target) r--;
            cout << l << " " << r;
            return 0;
        }
        if (sum < Target) l++;
        else r--;
    }

    cout << "No solution";
    return 0;
}
