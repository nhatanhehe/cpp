#include<bits/stdc++.h>
using namespace std;
#define Task "csq"
#define se second
#define fi first
#define ll long long
#define ii pair<ll, ll>
const long mxN = 400;

int nRow, nCol, n;
bitset<mxN> bit[4][mxN], base[mxN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".ans","w", stdout);
    }

    cin >> nRow >> nCol >> n;
    for (int i = 0; i < nRow; i++)
    {
        if (i)
            base[i] = base[i - 1];
        base[i].set(i);
        for (int j = 0; j < nCol; j++)
        {
            bit[0][i].set(j);
            bit[2][i].set(j);
            bit[1][j].set(i);
            bit[3][j].set(i);
        }
    }

    nCol--;
    nRow--;
    for (int i = 1; i <= n; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        bit[0][u].reset(v);
        bit[2][u].reset(nCol - v);
        bit[1][v].reset(u);
        bit[3][v].reset(nRow - u);
    }

    ll cnt = 0;
    for (int i = 0; i <= nRow; i++)
    {
        for (int j = 0; j <= nCol; j++)
        {
            for (int dis = 1; dis <= min(i, j); dis++)
                cnt += ((bit[3][j - dis] >> (nRow - i)) & (bit[2][i] >> (nCol - j)) & (bit[1][j] >> (i - dis)) & (bit[0][i - dis] >> (j - dis)) & base[dis - 1]).count();
        }
    }
    cout << cnt;
}

