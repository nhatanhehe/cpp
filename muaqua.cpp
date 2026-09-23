#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define Task "a"

ll k, n, s;
ll d[30][30];
ll dp[30][30][2005];

ll calc(int i, int lst, int sum){
    if (sum > s) return 0;
    if (i > k){
        return (sum == s);
    }
    ll &ans = dp[i][lst][sum];
    if (ans != -1) return ans;

    ans = 0;
    for(int j = 1; j <= n; j++){
        if (d[i][j] >= d[i-1][lst]) {
            ans += calc(i + 1, j, sum + d[i][j]);
        }
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    if (fopen(Task ".inp", "r")) {
        freopen(Task ".inp", "r", stdin);
        freopen(Task ".out", "w", stdout);
    }

    cin >> k >> n >> s;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= k; j++) cin >> d[j][i];
    }
    for(int i = 1; i <= k; i++){
        sort(d[i] + 1, d[i] + n + 1);
    }

    memset(dp, -1, sizeof dp);

    if (calc(1, 0, 0)) {
        cout << "YES\n";
    } else {
        cout << "NO";
        return 0;
    }
    ll sum = 0;
    int lst = 0;
    for(int i = 1; i <= k; i++){
        for(int j = 1; j <= n; j++){
            if (d[i][j] >= d[i-1][lst] && calc(i + 1, j, sum + d[i][j])) {
                sum += d[i][j];
                cout << d[i][j] << " ";
                lst = j;
                break;
            }
        }
    }

    return 0;
}
