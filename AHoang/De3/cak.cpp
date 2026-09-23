#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const ll INF = (ll)9e18;

struct SegmentTree {
    int n;
    vector<ll> tree;
    void init(int _n){
        n = _n;
        tree.assign(n*4 + 5, INF);
    }
    void up_internal(int pos, ll val, int id, int l, int r){
        if(l == r){
            tree[id] = min(tree[id], val);
            return;
        }
        int mid = (l+r)>>1;
        if(pos <= mid) up_internal(pos, val, id<<1, l, mid);
        else up_internal(pos, val, id<<1|1, mid+1, r);
        tree[id] = min(tree[id<<1], tree[id<<1|1]);
    }
    void up(int pos, ll val){
        if(pos < 1 || pos > n) return;
        up_internal(pos, val, 1, 1, n);
    }
    void reset(){
        fill(tree.begin(), tree.end(), INF);
    }
    ll get_internal(int u, int v, int id, int l, int r){
        if(l > v || r < u) return INF;
        if(u <= l && r <= v) return tree[id];
        int mid = (l+r)>>1;
        return min(get_internal(u,v,id<<1,l,mid), get_internal(u,v,id<<1|1,mid+1,r));
    }
    ll get(int u, int v){
        if(u>v) return INF;
        u = max(u,1); v = min(v,n);
        if(u>v) return INF;
        return get_internal(u,v,1,1,n);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if(!(cin >> n >> m)) return 0;
    vector<vector<int>> a(n+1, vector<int>(n+1));
    vector<vector<ii>> col(m+1); // dynamic by m
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> a[i][j];
            if(a[i][j] >= 1 && a[i][j] <= m){
                col[a[i][j]].push_back({i,j});
            }
        }
    }

    // if no points of color 1 or color m -> unreachable
    if(col[1].empty() || col[m].empty()){
        cout << -1 << '\n';
        return 0;
    }

    // dp arrays sized by max points in any color (but simpler: use per-color vectors)
    vector<ll> dp_before, dp_cur;

    // initialize dp_before for color 1 (distance from (1,1))
    dp_before.resize(col[1].size());
    sort(col[1].begin(), col[1].end(), [](const ii &x, const ii &y){
        if(x.first != y.first) return x.first < y.first;
        return x.second < y.second;
    });
    for(size_t i=0;i<col[1].size();++i){
        dp_before[i] = llabs(col[1][i].first - 1) + llabs(col[1][i].second - 1);
    }

    // process colors 2..m
    for(int k=2;k<=m;k++){
        if(col[k].empty()){
            cout << -1 << '\n';
            return 0;
        }
        // build tmp from previous color: tuples (x,y,cost)
        vector<iii> tmp;
        tmp.reserve(col[k-1].size());
        for(size_t i=0;i<col[k-1].size();++i){
            tmp.emplace_back(col[k-1][i].first, col[k-1][i].second, dp_before[i]);
        }
        sort(tmp.begin(), tmp.end(), [](const iii &A, const iii &B){
            return get<0>(A) < get<0>(B);
        });
        sort(col[k].begin(), col[k].end(), [](const ii &A, const ii &B){
            if(A.first != B.first) return A.first < B.first;
            return A.second < B.second;
        });

        dp_cur.assign(col[k].size(), INF);

        SegmentTree seg1, seg2;
        seg1.init(n+3);
        seg2.init(n+3);

        // Phase 1: xu >= xv (iterate increasing xu)
        int j = -1;
        for(size_t i=0;i<col[k].size();++i){
            while(j < (int)tmp.size()-1 && get<0>(tmp[j+1]) <= col[k][i].first){
                j++;
                int x = get<0>(tmp[j]);
                int y = get<1>(tmp[j]);
                ll dp = get<2>(tmp[j]);
                // seg1 stores dp - (x+y) at position y
                seg1.up(y, dp - (x + y));
                // seg2 stores dp - x + y at position y
                seg2.up(y, dp - x + y);
            }
            int xu = col[k][i].first;
            int yu = col[k][i].second;
            ll v1 = seg1.get(1, yu);
            if(v1 < INF) dp_cur[i] = min(dp_cur[i], xu + yu + v1);
            ll v2 = seg2.get(yu, n);
            if(v2 < INF) dp_cur[i] = min(dp_cur[i], xu - yu + v2);
        }

        // Phase 2: xu <= xv (iterate decreasing xu)
        seg1.reset();
        seg2.reset();
        j = (int)tmp.size();
        for(int i = (int)col[k].size()-1; i>=0; --i){
            while(j > 0 && get<0>(tmp[j-1]) >= col[k][i].first){
                j--;
                int x = get<0>(tmp[j]);
                int y = get<1>(tmp[j]);
                ll dp = get<2>(tmp[j]);
                // seg1 stores dp + x + y
                seg1.up(y, dp + x + y);
                // seg2 stores dp + x - y
                seg2.up(y, dp + x - y);
            }
            int xu = col[k][i].first;
            int yu = col[k][i].second;
            ll v1 = seg1.get(yu, n);
            if(v1 < INF) dp_cur[i] = min(dp_cur[i], v1 - (xu + yu));
            ll v2 = seg2.get(1, yu);
            if(v2 < INF) dp_cur[i] = min(dp_cur[i], v2 - (xu - yu));
        }

        dp_before = dp_cur; // move to next
    }

    ll ans = INF;
    for(ll v : dp_before) ans = min(ans, v);
    if(ans >= INF/2){
        cout << -1 << '\n';
    } else {
        cout << ans + 1 << '\n'; // giữ +1 như code gốc; nếu không cần, bỏ +1.
    }
    return 0;
}
