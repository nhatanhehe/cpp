#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define Task "a"
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf=1e18;
const ll N=5e4+5;
const ll mod=1e9+7;
const ll base=311;
const ll phainon=33550336;
#define On(mask,i) (mask|(1LL<<i))
#define Off(mask,i) (mask&~(1LL<<i))
inline ll add(ll a,ll b){
    ll res=a+b;
    if(res>=mod) res-=mod;
    return res;
}
ll sub(ll a,ll b){
    return ((a-b)%mod+mod)%mod;
}
inline ll mul(ll a,ll b){
    ll res=a*b;
    if(res>=mod) res%=mod;
    return res;
}
int n,m,a[N],dp[N][300],pw[N],sum;
ii Q[N];
int get(int mask,int i){
    return (mask/pw[i])%3;
}
int setb(int mask,int i,int val){
    int old=get(mask,i);
    mask-=old*pw[i];
    mask+=val*pw[i];
    return mask;
}
int cnt_1(int mask){
    int res=0;
    for(int j=0;j<m;j++){
        res+=(get(mask,j)==1);
    }
    return res;
}
int ro(int mask){
    for(int j=0;j<m;j++){
        if(get(mask,j)==1) return j;
    }
    return -1;
}
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cin>>n>>m;
    pw[0]=1;
    for(int i=1;i<=5;i++){
        pw[i]=pw[i-1]*3;
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum+=a[i]*m;
    }
    for(int i=0;i<m;i++){
        cin>>Q[i].fi>>Q[i].se;
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<pw[5];j++){
            dp[i][j]=-1e18;
        }
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++){

        // ---------- [START] PHẦN SỬA LỖI LOGIC ----------
        for(int mask=0; mask<pw[m]; mask++){
            if(dp[i-1][mask] == -1e18) continue;

            // 1. Tính trạng thái cơ sở (nmask_base)
            //    Chuyển tiếp 1->1, 1->2, 0->0, 2->2
            int nmask_base = 0;
            for (int j = 0; j < m; j++) {
                int bit = get(mask, j);
                if (bit == 2) {
                    nmask_base = setb(nmask_base, j, 2);
                } else if (bit == 0) {
                    nmask_base = setb(nmask_base, j, 0);
                } else { // bit == 1
                    // Nếu i nằm ngoài Q[j].se (hết hạn), segment j phải kết thúc (1 -> 2)
                    if (i > Q[j].se) {
                        nmask_base = setb(nmask_base, j, 2);
                    } else { // Ngược lại (vẫn trong hạn), segment j tiếp tục (1 -> 1)
                        nmask_base = setb(nmask_base, j, 1);
                    }
                }
            }

            // Cập nhật dp cho trạng thái cơ sở
            int first_active = ro(nmask_base); // Tìm bit 1 đầu tiên trong nmask_base
            int saving = (first_active == -1) ? 0 : (m - first_active) * a[i];
            dp[i][nmask_base] = max(dp[i][nmask_base], dp[i-1][mask] + saving);

            // 2. Tính các trạng thái "bắt đầu mới" (0 -> 1)
            //    Dựa trên trạng thái dp[i-1][mask]
            for (int j = 0; j < m; j++) {
                // Nếu bit j là 0 và i nằm trong đoạn [L, R] của j
                if (get(mask, j) == 0 && i >= Q[j].fi && i <= Q[j].se) {
                    // Bắt đầu segment j (0 -> 1)
                    // các bit khác (k != j) chuyển như trạng thái cơ sở (nmask_base)
                    int nmask = nmask_base;
                    nmask = setb(nmask, j, 1); // Bật bit j lên 1

                    first_active = ro(nmask); // Tìm lại bit 1 đầu tiên
                    saving = (m - first_active) * a[i];
                    dp[i][nmask] = max(dp[i][nmask], dp[i-1][mask] + saving);
                }
            }
        }
        // ---------- [END] PHẦN SỬA LỖI LOGIC ----------

        // Vòng lặp thứ 2 này là chính xác, dùng để xử lý các chuyển tiếp
        // 0 -> 2 và 1 -> 2 (chủ động kết thúc segment)
        for(int mask=0; mask<pw[m]; ++mask){
            if(dp[i][mask]==-1e18)continue;
            for(int j=0; j<m; j++){
                // Nếu i >= L_j, ta có thể chọn "kết thúc" vòng j
                // (cho dù nó đang là 0 hay 1)
                if(Q[j].fi<=i){
                    int x=get(mask,j);
                    if(x == 2) continue; // Đã kết thúc rồi thì thôi
                    int nmask=mask-pw[j]*x+pw[j]*2;
                    dp[i][nmask]=max(dp[i][nmask],dp[i][mask]);
                }
            }
        }
    }
    cout<<sum-dp[n][pw[m]-1];
}
