#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
const int mod = 998244353;

string s;
map<string,int> mp;
vector<string> forb;
int mat[150][150];
int cnt = 1;

bool fo(const string &s) {
    for (const string &f : forb)
        if (s.find(f) != string::npos)
            return true;
    return false;
}

void ql(int i, string res, int last) {
    if (i > 6) return;
    string sa = res + "a", sb = res + "b";
    if (!mp.count(sa)) mp[sa] = ++cnt;
    if (!mp.count(sb)) mp[sb] = ++cnt;
    if (!fo(sa)) {
        mat[last][mp[sa]] = 1;
        ql(i + 1, sa, mp[sa]);
    }
    if (!fo(sb)) {
        mat[last][mp[sb]] = 1;
        ql(i + 1, sb, mp[sb]);
    }
}

inline int add(int a,int b){ a+=b; if(a>=mod) a-=mod; return a; }
inline int mul(int a,int b){ return (a*b)%mod; }

struct Matrix {
    int x[150][150];
    Matrix() { memset(x, 0, sizeof(x)); }
    Matrix operator*(const Matrix &b) const {
        Matrix c;
        for (int i = 1; i <= cnt; i++)
            for (int k = 1; k <= cnt; k++) if (x[i][k])
                for (int j = 1; j <= cnt; j++)
                    c.x[i][j] = add(c.x[i][j], mul(x[i][k], b.x[k][j]));
        return c;
    }
};

Matrix power(Matrix base, long long p) {
    Matrix res;
    for (int i = 1; i <= cnt; i++) res.x[i][i] = 1;
    while (p) {
        if (p & 1) res = res * base;
        base = base * base;
        p >>= 1;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    forb.resize(m);
    for (int i = 0; i < m; i++) cin >> forb[i];

    mp[""] = 1;
    ql(1, "", 1);

    Matrix A;
    for (int i = 1; i <= cnt; i++)
        for (int j = 1; j <= cnt; j++)
            A.x[i][j] = mat[i][j];

    Matrix B = power(A, n);

    int ans = 0;
    for (int i = 1; i <= cnt; i++)
        ans = add(ans, B.x[1][i]);
    cout << ans;
}
