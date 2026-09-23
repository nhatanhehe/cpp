#include <bits/stdc++.h>
using namespace std;

/**
 * Description: Tarjan's, DFS once to generate
 * strongly connected components in topological order. $a,b$
 * in same component if both $a\to b$ and $b\to a$ exist.
 * Uses less memory than Kosaraju b/c doesn't store reverse edges.
 * Time: O(N+M)
 * Source: KACTL
 * https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/SCC.h
 * Verification: https://cses.fi/problemset/task/1686/
 */

struct SCC {
	int N, ti = 0;
	vector<vector<int>> adj;
	vector<int> disc, comp, st, comps;
	void init(int _N) {
		N = _N;
		adj.resize(N), disc.resize(N), comp = vector<int>(N, -1);
	}
	void ae(int x, int y) { adj[x].push_back(y); }
	int dfs(int x) {
		int low = disc[x] = ++ti;
		st.push_back(x);  // disc[y] != 0 -> in stack
		for (int y : adj[x])
			if (comp[y] == -1) low = min(low, disc[y] ?: dfs(y));
		if (low == disc[x]) {  // make new SCC, pop off stack until you find x
			comps.push_back(x);
			for (int y = -1; y != x;) comp[y = st.back()] = x, st.pop_back();
		}
		return low;
	}
	void gen() {
		for (int i = 0; i < N; i++)
			if (!disc[i]) dfs(i);
		reverse(begin(comps), end(comps));
	}
};

int main() {

	int n, m, a, b;
	cin >> n >> m;

	SCC graph;
	graph.init(n);
	while (m--) {
		cin >> a >> b;
		graph.ae(--a, --b);
	}
	graph.gen();

	int ID[200000]{};
	int ids = 0;
	for (int i = 0; i < n; i++) {
		if (!ID[graph.comp[i]]) { ID[graph.comp[i]] = ++ids; }
	}
	cout << ids << '\n';
	for (int i = 0; i < n; i++) { cout << ID[graph.comp[i]] << " \n"[i == n - 1]; }
}
