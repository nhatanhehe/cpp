#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define debug(x) cout<< #x << " = "<< x <<'\n'
#define Task "a"
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf=1e18;
const ll N=1e6+5;
const ll mod=1e9+7;
inline ll add(ll a,ll b){
    ll res=a+b;
    if(res>=mod) res-=mod;
    return res;
}
ll sub(ll a,ll b){
    ll res = a - b;
    if (res < 0) res += mod;
    return res;
}
ll n, dp[N], cnt['z'+3], ans;
string s;
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }

    cin >> n >> s;
    s = " " + s;
    ans = 0;
    for(int d = 1; d <= 26; d++){
        int dist = 0;
        memset(cnt, 0, sizeof cnt);
        for(int i=0; i<=n+1; i++) dp[i] = 0;

        vector<ll> mn(n+5, -1), mx(n+5, -1), pre(n+5, 0);
        memset(cnt, 0, sizeof cnt);
        dist = 0;
        int l = 1;
        for(int r = 1; r <= n; r++){
            cnt[s[r]]++;
            if(cnt[s[r]] == 1) dist++;

            while(dist > d && l <= r){
                cnt[s[l]]--;
                if(cnt[s[l]] == 0) dist--;
                l++;
            }

            if(dist == d) mn[r] = l;
            else mn[r] = -1;
        }
        memset(cnt, 0, sizeof cnt);
        dist = 0;
        l = 1;
        for(int r = 1; r <= n; r++){
            cnt[s[r]]++;
            if(cnt[s[r]] == 1) dist++;

            while(dist > d && l <= r){
                cnt[s[l]]--;
                if(cnt[s[l]] == 0) dist--;
                l++;
            }
            while(dist == d && l < r && cnt[s[l]] > 1){
                cnt[s[l]]--;
                l++;
            }
            if(dist == d) mx[r] = l;
            else mx[r] = -1;
        }
        pre[0] = 0;
        for(int i = 1; i <= n; i++){
            int l = mn[i], r = mx[i];
            if(l != -1 && r != -1 && l <= r){
                ll w1 = r - l + 1;
                ll w2 = sub(pre[r - 1], pre[max(0ll, l - 2)]);
                dp[i] = add(w1, w2);
                ans = add(ans, w2);
            } else {
                dp[i] = 0;
            }

            pre[i] = add(pre[i-1], dp[i]);
        }
    }

    cout << ans;
}
