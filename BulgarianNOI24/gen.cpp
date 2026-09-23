#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 6) {
        cerr << "Usage: " << argv[0] << " <seed> <subtask_type> <n> <q> <maxW>" << endl;
        return 1;
    }

    int seed = stoi(argv[1]);
    int subtask_type = stoi(argv[2]);
    int n = stoi(argv[3]);
    int q = stoi(argv[4]);
    int maxW = stoi(argv[5]);

    srand(seed);

    // Ensure n >= 1
    if (n < 1) n = 1;
    if (n == 1) {
        // Special case: single node tree
        cout << n << '\n';
        // No edges
        cout << q << '\n';
        // Generate queries
        int total_k = 0;
        const int MAX_TOTAL_K = 200000;
        for (int i = 0; i < q; i++) {
            int type;
            if (subtask_type == 4) { // Static tree: no type 2 queries
                type = 1;
            } else {
                type = rand() % 2 + 1; // 1 or 2
            }

            cout << type << ' ';
            if (type == 1) {
                int x = rand() % n + 1;
                int k = 0;
                if (subtask_type != 3) { // Not the k=0 subtask
                    // Generate k such that total_k doesn't exceed limit
                    int remaining = MAX_TOTAL_K - total_k;
                    if (remaining > 0) {
                        // Limit k per query to avoid using too much at once
                        int max_k_per_query = min(10, remaining);
                        k = rand() % (max_k_per_query + 1);
                    }
                    total_k += k;
                }
                cout << x << ' ' << k;
                vector<int> forbidden;
                for (int j = 0; j < k; j++) {
                    int forbid = rand() % n + 1;
                    forbidden.push_back(forbid);
                }
                // Sort and remove duplicates (optional but clean)
                sort(forbidden.begin(), forbidden.end());
                forbidden.erase(unique(forbidden.begin(), forbidden.end()), forbidden.end());
                k = forbidden.size(); // Update k after dedup
                for (int forbid : forbidden) {
                    cout << ' ' << forbid;
                }
                cout << '\n';
            } else { // type == 2
                if (n == 1) {
                    // No edges to update, skip or make dummy query
                    cout << "1 1 1\n"; // dummy edge id 1 (doesn't exist but we'll handle)
                } else {
                    int id = rand() % (n-1) + 1;
                    int w = rand() % maxW + 1;
                    cout << id << ' ' << w << '\n';
                }
            }
        }
        return 0;
    }

    // Generate tree based on subtask type
    vector<pair<int, int>> edges;
    vector<int> weights;

    if (subtask_type == 2) {
        // Path graph (max degree <= 2)
        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 1);
        random_shuffle(perm.begin(), perm.end());
        for (int i = 0; i < n-1; i++) {
            int u = perm[i];
            int v = perm[i+1];
            int w = rand() % maxW + 1;
            edges.push_back({u, v});
            weights.push_back(w);
        }
    } else {
        // Random tree using Prufer sequence
        vector<int> degree(n+1, 1);
        vector<int> prufer(n-2);
        for (int i = 0; i < n-2; i++) {
            prufer[i] = rand() % n + 1;
            degree[prufer[i]]++;
        }

        set<int> leaves;
        for (int i = 1; i <= n; i++) {
            if (degree[i] == 1) leaves.insert(i);
        }

        for (int i = 0; i < n-2; i++) {
            int leaf = *leaves.begin();
            leaves.erase(leaves.begin());

            int u = leaf;
            int v = prufer[i];
            int w = rand() % maxW + 1;
            edges.push_back({u, v});
            weights.push_back(w);

            degree[u]--;
            degree[v]--;
            if (degree[v] == 1) leaves.insert(v);
        }

        // Last edge
        int u = *leaves.begin();
        leaves.erase(leaves.begin());
        int v = *leaves.begin();
        int w = rand() % maxW + 1;
        edges.push_back({u, v});
        weights.push_back(w);
    }

    // Output tree
    cout << n << '\n';
    for (int i = 0; i < n-1; i++) {
        cout << edges[i].first << ' ' << edges[i].second << ' ' << weights[i] << '\n';
    }

    // Output number of queries
    cout << q << '\n';

    // Generate queries
    int total_k = 0;
    const int MAX_TOTAL_K = 200000;
    for (int i = 0; i < q; i++) {
        int type;
        if (subtask_type == 4) { // Static tree: no type 2 queries
            type = 1;
        } else {
            type = rand() % 2 + 1; // 1 or 2
        }

        cout << type << ' ';
        if (type == 1) {
            int x = rand() % n + 1;
            int k = 0;
            if (subtask_type != 3) { // Not the k=0 subtask
                // Generate k such that total_k doesn't exceed limit
                int remaining = MAX_TOTAL_K - total_k;
                if (remaining > 0) {
                    // Limit k per query to avoid using too much at once
                    int max_k_per_query = min(10, remaining);
                    k = rand() % (max_k_per_query + 1);
                }
                total_k += k;
            }
            cout << x << ' ' << k;
            vector<int> forbidden;
            for (int j = 0; j < k; j++) {
                int forbid = rand() % n + 1;
                forbidden.push_back(forbid);
            }
            // Sort and remove duplicates (optional but clean)
            sort(forbidden.begin(), forbidden.end());
            forbidden.erase(unique(forbidden.begin(), forbidden.end()), forbidden.end());
            k = forbidden.size(); // Update k after dedup
            for (int forbid : forbidden) {
                cout << ' ' << forbid;
            }
            cout << '\n';
        } else { // type == 2
            if (n == 1) {
                // No edges to update, make dummy query (will be ignored by solution if edge doesn't exist)
                cout << "1 1 1\n";
            } else {
                int id = rand() % (n-1) + 1;
                int w = rand() % maxW + 1;
                cout << id << ' ' << w << '\n';
            }
        }
    }

    return 0;
}