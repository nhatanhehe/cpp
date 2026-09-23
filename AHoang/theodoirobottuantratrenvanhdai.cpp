#include<bits/stdc++.h>
using namespace std;
#define ll long long
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
const int N = 200000 + 5;
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
int n,m,a[N],b[N],l[N],r[N],S[N];
struct SparseSegtree {
private:
    struct Node {
        int freq = 0;
        int set = -1;
        Node *l = nullptr, *r = nullptr;
    };
    Node *root;
    const int n;

    void apply_set(Node *cur, int len, int v) {
        cur->set = v;
        cur->freq = v ? len : 0;
    }

    void ensure_child(Node *&child, int len) {
        if (!child) {
            child = new Node();
            apply_set(child, len, 1);
        }
    }

    void push_down(Node *cur, int l, int r) {
        if (cur->set == -1) return;
        int m = (l + r) >> 1;
        int lenL = m - l + 1;
        int lenR = r - m;
        ensure_child(cur->l, lenL);
        ensure_child(cur->r, lenR);
        apply_set(cur->l, lenL, cur->set);
        apply_set(cur->r, lenR, cur->set);
        cur->set = -1;
    }

    void pull(Node *cur) {
        int a = cur->l ? cur->l->freq : 0;
        int b = cur->r ? cur->r->freq : 0;
        cur->freq = a + b;
    }

    void range_clear(Node *cur, int l, int r, int ql, int qr) {
        if (qr < l | ql > r) return;
        if (ql <= l && r <= qr) {
            apply_set(cur, r - l + 1, 0);
            return;
        }
        push_down(cur, l, r);
        int m = (l + r) >> 1;
        if (ql <= m) {
            ensure_child(cur->l, m - l + 1);
            range_clear(cur->l, l, m, ql, qr);
        }
        if (qr > m) {
            ensure_child(cur->r, r - m);
            range_clear(cur->r, m + 1, r, ql, qr);
        }
        pull(cur);
    }

    int range_sum(Node *cur, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) {
            return cur->freq;
        }
        if (cur->set == 1) {
            int L = max(l, ql);
            int R = min(r, qr);
            return (L <= R) ? (R - L + 1) : 0;
        }
        if (cur->set == 0) return 0;

        int m = (l + r) >> 1;
        int res = 0;
        if (ql <= m) {
            if (cur->l) res += range_sum(cur->l, l, m, ql, qr);
            else {
                int L = max(l, ql);
                int R = min(m, qr);
                if (L <= R) res += (R - L + 1);
            }
        }
        if (qr > m) {
            if (cur->r) res += range_sum(cur->r, m + 1, r, ql, qr);
            else {
                int L = max(m + 1, ql);
                int R = min(r, qr);
                if (L <= R) res += (R - L + 1);
            }
        }
        return res;
    }

public:
    SparseSegtree(int n) : n(n) {
        root = new Node();
        apply_set(root, n, 1);
    }

    void range_clear(int ql, int qr) {
        if (ql > qr) return;
        range_clear(root, 0, n - 1, ql, qr);
    }

    int range_sum(int ql, int qr) {
        if (ql > qr) return 0;
        return range_sum(root, 0, n - 1, ql, qr);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cin>>n>>m;
    int s=0;
    SparseSegtree st(n+3);
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        u=(u+s)%n;
        v=(v+s)%n;
        if(u<=v){
            st.range_clear(0,u-1);
            st.range_clear(v+1,n-1);
        }
        else{
            st.range_clear(v+1,u-1);
        }
        cout<<(s=st.range_sum(0,n-1))<<'\n';
    }
}
