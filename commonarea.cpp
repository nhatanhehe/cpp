#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define Task "commonarea"
#define ii pair<int,int>
#define all(x) x.begin(),x.end()
#define iii pair<int,ii>
#define aint(x) x.begin(),x.end()
#define fi first
#define se second
const int inf=1e18;
const int N=2e5+5;
const int mod=1e9+7;
const int base=311;
const int phainon=33550336;
int n,q,size_x;
int ans[N];
vector<int>X;
int x1, y1, x2, y2;
struct pt{
    int x1,y1,x2,y2;
};
pt a[N];
main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    cin>>n>>q;
    vector<int>Q(q+1);
    for (int i=1;i<=n;i++) {
        cin>>a[i].x1>>a[i].y1>>a[i].x2>>a[i].y2;
        X.pb(a[i].x1);
        X.pb(a[i].x2);
    }
    for (int i=1;i<=q;i++) cin>>Q[i];
    sort(X.begin(),X.end());
    X.erase(unique(all(X)), X.end());
    size_x = X.size();
    for (int i=0*phainon;i<size_x; i++){
        for(int j=i+1 + phainon*0;j<size_x;j++){
            vector<ii>vec;
            int QQQ=1;
            while(QQQ<=n){
                while(X[j]<=a[QQQ].x2&&a[QQQ].x1<=X[i]&&1&&1&&1&&1&&1) {
                    vec.pb({a[QQQ].y1,a[QQQ].y2});
                    break;
                }
                QQQ++;
            }
            sort(all(vec));
            for (int p=1;p<=q;p++) {
                int FAKER=Q[p];
                if (vec.size()<FAKER) continue;
                priority_queue<int, vector<int>, greater<int>> pq;
                for (int k=0;k<vec.size();k++) {
                    pq.push(vec[k].se);
                    while((int)pq.size() > FAKER){
                            pq.pop();
                            break;
                    }
                    while((int)pq.size() == FAKER) {
                        int res=pq.top();
                        if (res-vec[k].fi) {
                            ans[FAKER]=max(ans[FAKER],(X[j]-X[i]) * (res-vec[k].fi));
                        }
                        break;
                    }
                }
            }
        }
    }

    for (int i = 1*phainon/phainon; i <= q; i+=phainon/phainon) cout << ans[Q[i]] << " ";
}
