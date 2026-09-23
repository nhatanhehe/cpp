#include <bits/stdc++.h>
#define task "a"
#define ll long long
#define ld long double
#define ii pair<int, int>
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define mems(x, y) memset(x, y, sizeof(x));
using namespace std;
const int mod = 1e9 + 7, moi = 5e5 + 9;
const ll INF = 1e18;
const ld EFS = 1e-12;
const int dx[] = { 1, -1, 0, 0};
const int dy[] = { 0, 0, 1, -1};

struct pt {

};

int c, n;
int v[moi];

// LAST SUM

int last[moi];

void last_sum() {

    last[0] = c;
    for(int i = 1; i <= n; i++) {
        last[i] = last[i - 1];
        if(last[i] >= v[i]) last[i] -= v[i];
    }
}


// TIEN XU LI

int nx[moi], cnt[moi], pos[moi];
ll pre[moi];

void prepare() {
    for(int i = 1; i <= n; i++) {
        cnt[v[i]]++;
    }

    nx[0] = 0;
    for(int i = 1; i <= c; i++) {
        if(cnt[i] > 0) nx[i] = i;
        else nx[i] = nx[i - 1];
    }

    pre[0] = 0;
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + v[i];
    }

    for(int i = 0; i <= c; i++) pos[i] = n;

    int j = c;
    pos[j] = 0;

    for(int i = 1; i <= n; i++) {
        while(j >= v[i] && j > 0) {
            pos[j - 1] = pos[j];
            j--;
        }

        pos[j] = i;
    }
}

// FIND DOAN

int find_right(int S, int i) {
    int position = upper_bound(pre + 1, pre + n + 1, S + pre[i - 1]) - pre - 1;
    return position;
}

// RESET

void reset() {
    for(int i = 0; i <= c; i++) {
        nx[i] = 0;
        cnt[i] = 0;
    }

}

void Input() {
    cin >> c >> n;
    reset();

    for(int i = 1; i <= n; i++) cin >> v[i];

    sort(v + 1, v + n + 1, greater<int>());

    last_sum();
    prepare();

    //for(int i = 1; i <= c; i++) cout << i << " " << pos[i] << '\n';

    for(int i = 1; i <= c; i++) {

        int vt = pos[i];
        int sum = last[vt];

        if(sum >= i) sum -= i;
        int left = max(pos[sum] + 1, pos[i] + 1);

        while(sum) {
            if(left == n + 1) break;

            int right = find_right(sum, left);

            sum -= (pre[right] - pre[left - 1]);
            left = max(right + 1, pos[sum] + 1);
        }

        if(sum > 0) {
            cout << i << " ";
            return;
        }
    }

    cout << "-1 ";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    if(fopen(task".inp","r")){
        freopen(task".inp","r",stdin);
        freopen(task".ans","w",stdout);
    }

    int subtask;
    int t = 1;
    while (t --) {
        Input();
    }

    cerr << "Time: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s.\n";
}
