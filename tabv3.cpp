#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define all(x) x.begin(),x.end()
#define fi first
#define se second
#define Task "a"
const int N = 2005;

int n, m, d;
ll a[N][N];

struct seg2D {
    int n, m;
    int tree[4*N][4*N];
    seg2D(){
        memset(tree,0,sizeof tree);
    }

    void updateY(int idX, int lX, int rX, int idY, int lY, int rY, int x, int y, int val) {
        if (lY == rY) {
            if (lX == rX) tree[idX][idY] = max(tree[idX][idY], val);
            else tree[idX][idY] = max(tree[idX*2][idY], tree[idX*2+1][idY]);
            return;
        }
        int midY = (lY + rY)/2;
        if (y <= midY) updateY(idX, lX, rX, idY*2, lY, midY, x, y, val);
        else updateY(idX, lX, rX, idY*2+1, midY+1, rY, x, y, val);
        tree[idX][idY] = max(tree[idX][idY*2], tree[idX][idY*2+1]);
    }

    void update(int idX, int lX, int rX, int x, int y, ll val) {
        if (lX != rX) {
            int midX = (lX + rX)/2;
            if (x <= midX) update(idX*2, lX, midX, x, y, val);
            else update(idX*2+1, midX+1, rX, x, y, val);
        }
        updateY(idX, lX, rX, 1, 1, m, x, y, val);
    }

    ll getY(int idX, int idY, int lY, int rY, int y1, int y2) {
        if (y1 > rY || y2 < lY) return 0;
        if (y1 <= lY && rY <= y2) return tree[idX][idY];
        int midY = (lY + rY)/2;
        return max(getY(idX, idY*2, lY, midY, y1, y2), getY(idX, idY*2+1, midY+1, rY, y1, y2));
    }

    ll get(int idX, int lX, int rX, int x1, int x2, int y1, int y2) {
        if (x1 > rX || x2 < lX) return 0;
        if (x1 <= lX && rX <= x2) return getY(idX, 1, 1, m, y1, y2);
        int midX = (lX + rX)/2;
        return max(get(idX*2, lX, midX, x1, x2, y1, y2), get(idX*2+1, midX+1, rX, x1, x2, y1, y2));
    }

    ll query(int x1, int y1, int x2, int y2) {
        return get(1, 1, n, x1, x2, y1, y2);
    }
};

struct pt {
    int val, i, j;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }

    cin >> n >> m >> d;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j];

    vector<pt> g;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            g.pb({(int)a[i][j], i, j});

    sort(all(g), [](const pt &x, const pt &y) { return x.val < y.val; });

    int OFFSET = m;
    seg2D seg;
    seg.n = 2000;
seg.m = 2000;
    int cur = -2e9;
    vector<pt> change;
    int ans = 0;

    for (auto [val, i, j] : g) {
        if (val != cur) {
            for (auto [v_,x_, y_] : change) {
                seg.update(1, 1, seg.n, x_, y_, v_);
            }
            change.clear();
            cur = val;
        }
        int u=i+j;
        int v=i-j+m;
        int x1 =max(1,u-d);
        int y1 =max(1,v-d);
        int x2 =min(2000, u+ d);
        int y2 =min(v+ d,2000);

        ll V = seg.query(x1, y1, x2, y2) + 1;
        ans = max(ans, (int)V);

        change.pb({V,u,v});
      //  seg.update(1, 1, seg.n, i+j+OFFSET, i-j+OFFSET, V);
    }

    cout << ans << "\n";
    return 0;
}
