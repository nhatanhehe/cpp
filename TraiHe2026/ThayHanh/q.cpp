    #include<bits/stdc++.h>
    using namespace std;
    #define ll long long
    typedef long double ld;
    #define pb push_back
    #define pf push_front
    #define debug(x) cout<< #x << " = "<< x <<'\n'
    #define Task "antiqueen"
    #define ii pair<int,int>
    #define iii pair<int,ii>
    #define all(x) x.begin(),x.end()
    #define fi first
    #define se second
    const ll inf=1e18;
    const ll N=2e5+5;
    const ll mod=998244353;
    const ll base=311;
    const ll phainon=33550336;

    inline ll add(ll a, ll b) {
        ll res = a + b;
        if(res >= mod) res -= mod;
        return res;
    }

    ll sub(ll a, ll b) {
        return ((a - b) % mod + mod) % mod;
    }

    inline ll mul(ll a, ll b) {
        ll res = a * b;
        if(res >= mod) res %= mod;
        return res;
    }

    ll r,c,n,dp[2][230][230],diag1[2][230*2],diag2[2][230*2],row[2][230],col[2][230],sum[2]; // Thu nhỏ sum thành [2] luôn

    void calc(int st){
        sum[st] = 0; // 2. Sửa lỗi: Cần reset sum về 0 trước khi tính tầng mới

        for(int i=1;i<=r;i++){
            row[st][i]=0;
            for(int j=1;j<=c;j++){
                row[st][i]=add(row[st][i],dp[st][i][j]);
                sum[st]=add(dp[st][i][j],sum[st]);
            }
        }
        for(int j=1;j<=c;j++){
            col[st][j]=0;
            for(int i=1;i<=r;i++){
                col[st][j]=add(col[st][j],dp[st][i][j]);
            }
        }
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                diag1[st][i-j+c]=0;
                diag2[st][i+j]=0;
            }
        }
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                diag1[st][i-j+c]=add(diag1[st][i-j+c],dp[st][i][j]);
                diag2[st][i+j]=add(diag2[st][i+j],dp[st][i][j]);
            }
        }
    }

    int main(){
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);cout.tie(NULL);
        if (fopen(Task ".inp","r")) {
            freopen(Task ".inp","r", stdin);
            freopen(Task ".out","w", stdout);
        }
        cin>>r>>c>>n;
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                dp[0][i][j]=1;
            }
        }
        calc(0);
        int cur=0;
        for(int t=1;t<=n;t++){
            int next_cur = cur ^ 1;
            for(int i=1;i<=r;i++){
                for(int j=1;j<=c;j++){
                    ll bi_tru = add(row[cur][i], col[cur][j]);
                    bi_tru = add(bi_tru, diag1[cur][i-j+c]);
                    bi_tru = add(bi_tru, diag2[cur][i+j]);
                    bi_tru = sub(bi_tru, mul(3, dp[cur][i][j]));
                    dp[next_cur][i][j] = sub(sum[cur], bi_tru);
                }
            }
            calc(next_cur);
            cur = next_cur;
        }

        ll ans=0;
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                ans=add(ans,dp[cur][i][j]);
            }
        }
        cout<<ans;
        return 0;
    }
