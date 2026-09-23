#include <bits/stdc++.h>  // see C++ Tips & Tricks
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int, int>;
#define f first
#define s second
#define mp make_pair

void setIO(string name = "") {  // name is nonempty for USACO file I/O
	ios_base::sync_with_stdio(0);
	cin.tie(0);  // see Fast Input & Output
	// alternatively, cin.tie(0)->sync_with_stdio(0);
	if (sz(name)) {
		freopen((name + ".in").c_str(), "r", stdin);  // see Input & Output
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

vi adj[100005][2];
bool vis[100005];

void dfs(int v, int x) {
	vis[v] = true;
	for (int to : adj[v][x]) {
		if (!vis[to]) { dfs(to, x); }
	}
}

int main() {
	setIO();
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		adj[u][0].pb(v);
		adj[v][1].pb(u);
	}
	dfs(0, 0);
	for (int i = 0; i < n; i++) {
		if (!vis[i]) {
			cout << "NO" << '\n';
			cout << 1 << " " << i + 1 << '\n';
			return 0;
		}
	}
	memset(vis, false, sizeof(vis));  // fill vis with false
	dfs(0, 1);
	for (int i = 0; i < n; i++) {
		if (!vis[i]) {
			cout << "NO" << '\n';
			cout << i + 1 << " " << 1 << '\n';
			return 0;
		}
	}
	cout << "YES" << '\n';
}
