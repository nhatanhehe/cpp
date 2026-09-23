#include <bits/stdc++.h>
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define Task "a"
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf = 1e18;
const int MAXV = 3000;
vector<int> uoc[MAXV+5];
void sang(){
    for(int i=1;i<=MAXV;i++){
        for(int j=i;j<=MAXV;j+=i){
            uoc[j].pb(i);
        }
    }
}
int m,n;
int a[3005][3005], pre[3005][3005];

int sum(int x1,int y1,int x2,int y2){
    return pre[x2][y2] - pre[x1-1][y2] - pre[x2][y1-1] + pre[x1-1][y1-1];
}

bool check(int i,int j){
    for(int x=1;x<=m;x+=i){
        for(int y=1;y<=n;y+=j){
            int nx = x + i - 1;
            int ny = y + j - 1;
            int val = sum(x,y,nx,ny);
            if(val != 0 && val != i*j) return false;
        }
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (fopen(Task ".inp","r")) {
        freopen(Task ".inp","r", stdin);
        freopen(Task ".out","w", stdout);
    }
    sang();
    cin >> m >> n;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            char x; cin >> x;
            a[i][j] = x - '0';
            pre[i][j] = pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1] + a[i][j];
        }
    }
    int ans = 0, bx = 1, by = 1;
    for(int i : uoc[m]){
        for(int j : uoc[n]){
            if(check(i,j)){
                if(ans < i*j){
                    ans = i*j;
                    bx = i; by = j;
                }
            }
        }
    }

    cout << m/bx << " " << n/by << '\n';
    for(int x=1;x<=m;x+=bx){
        for(int y=1;y<=n;y+=by){
            int nx = x + bx - 1;
            int ny = y + by - 1;
            int val = sum(x,y,nx,ny);
            cout << (val == 0 ? '0' : '1');
        }
        cout << '\n';
    }
    return 0;
}
