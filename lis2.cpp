#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define Task "lis2"
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf=1e18;
const ll N=6e5+5;
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

// fast input
inline int get_char() {
    static const int BUF_SIZE = 1 << 16;
    static char buf[BUF_SIZE], *ptr = buf + BUF_SIZE, *end = buf + BUF_SIZE;
    if (ptr == end) {
        ptr = buf;
        end = buf + fread(buf, 1, BUF_SIZE, stdin);
        if (ptr == end) return EOF;
    }
    return *ptr++;
}

inline int read_int() {
    int x = 0, f = 1;
    int ch = get_char();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = get_char();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = get_char();
    }
    return x * f;
}

// fast output
inline void write_int(int x) {
    static char buf[20];
    int len = 0;
    if (x == 0) {
        putchar('0');
        putchar('\n');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    while (x) {
        buf[len++] = (x % 10) + '0';
        x /= 10;
    }
    for (int i = len-1; i >=0; i--) putchar(buf[i]);
    putchar('\n');
}

int a[N],p[N],q,n,x[N],cnt,bit1[N],bit2[N],dp1[N],dp2[N],LIS,x1[N],x2[N],fl[N],fr[N];
map<int,int>mp;
inline void up1(int pos, int k, int bit[], int n) {
    for (; pos <= n; pos += pos & -pos) {
        bit[pos] = max(bit[pos], k);
    }
}
inline int get1(int pos, int bit[]) {
    int res = 0;
    for (; pos > 0; pos -= pos & -pos) {
        res = max(res, bit[pos]);
    }
    return res;
}
inline void up2(int pos, int k, int bit[]) {
    for (; pos > 0; pos -= pos & -pos) {
        bit[pos] = max(bit[pos], k);
    }
}
inline int get2(int pos, int bit[], int n) {
    int res = 0;
    for (; pos <= n; pos += pos & -pos) {
        res = max(res, bit[pos]);
    }
    return res;
}
int cn[N];
struct pt{
    int p,x,id;
}Q[N];

main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }

    n = read_int();
    q = read_int();
    vector<int>cp;
    for(int i=1;i<=n;i++){
        a[i] = read_int();
        cp.pb(a[i]);
    }
    for(int i=1;i<=q;i++){
        p[i] = read_int();
        x[i] = read_int();
        cp.pb(x[i]);
    }
    sort(all(cp));
    cp.erase(unique(all(cp)),cp.end());
    cnt=cp.size();
    for(int i=1;i<=n;i++) a[i]=lower_bound(all(cp),a[i])-cp.begin()+1;
    for(int i=1;i<=q;i++){
        x[i]=lower_bound(all(cp),x[i])-cp.begin()+1;
        Q[i]={p[i],x[i],i};
    }
    for(int i=1;i<=n;i++){
        dp1[i]=get1(a[i]-1, bit1)+1;
        up1(a[i],dp1[i], bit1, cnt);
    }
    LIS=*max_element(dp1+1,dp1+n+1);
    for(int i=n;i>=1;i--){
        dp2[i]=get2(a[i]+1, bit2, cnt)+1;
        up2(a[i],dp2[i], bit2);
    }

    for(int i=1;i<=n;i++){
        if(dp1[i]+dp2[i]-1==LIS) cn[dp1[i]]++;
    }
    sort(Q+1,Q+q+1,[&](const pt &x,const pt &y){
        return x.p<y.p;
    });
    memset(bit1,0,sizeof bit1);
    int j=0;
    for(int i=1;i<=q;i++){
        auto [p1,x1,id]=Q[i];
        while(j<n&&j+1<p1){
            j++;
            up1(a[j],dp1[j], bit1, cnt);
        }
        fl[id]=get1(x1-1, bit1)+1;
    }
    memset(bit2,0,sizeof bit2);
    sort(Q+1,Q+q+1,[&](const pt &x,const pt &y){
        return x.p>y.p;
    });
    j=n+1;
    for(int i=1;i<=q;i++){
        auto [p1,x1,id]=Q[i];
        while(j>1&&j-1>p1){
            j--;
            up2(a[j],dp2[j], bit2);
        }
        fr[id]=get2(x1+1, bit2, cnt)+1;
    }
    for(int i=1;i<=q;i++){
        int x1_,x2_;
        if(dp1[p[i]]+dp2[p[i]]-1==LIS&&cn[dp1[p[i]]]==1){
            x1_=LIS-1;
        }
        else x1_=LIS;
        x2_=fl[i]+fr[i]-1;
        write_int(max(x1_,x2_));
    }
}
