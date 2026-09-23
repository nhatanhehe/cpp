#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " <seed> <n_max> <l_max> <mode>" << endl;
        return 1;
    }

    long long seed = stoll(argv[1]);
    int n_max = stoi(argv[2]);
    int l_max = stoi(argv[3]);
    int mode = stoi(argv[4]);

    mt19937_64 rng(seed);
    uniform_int_distribution<int> dist_n(1, n_max);
    uniform_int_distribution<int> dist_l(1, l_max);
    uniform_int_distribution<int> dist_h(1, 1000000000); // H_i up to 1e9
    uniform_int_distribution<int> dist_w_small(1, 5);   // for killer small widths

    int n = dist_n(rng);
    int L = dist_l(rng);

    // Adjust n and L for certain modes to maximize stress
    if (mode == 0) {
        // random: keep as is
    } else if (mode == 1 || mode == 2) {
        // large/small W_i: keep as is
    } else if (mode >= 3 && mode <= 5) {
        // monotonic and spike modes: use max n to stress
        n = n_max;
    } else if (mode >= 6 && mode <= 8) {
        // Killer cases: use max n and max L
        n = n_max;
        L = l_max;
    }

    // Handle edge case where n=1 to avoid division by zero
    if (n == 1) {
        vector<int> H(2), W(2);
        H[1] = dist_h(rng);
        W[1] = uniform_int_distribution<int>(1, L)(rng);
        cout << n << " " << L << "\n";
        cout << H[1] << " " << W[1] << "\n";
        return 0;
    }

    vector<int> H(n+1), W(n+1); // 1-indexed

    if (mode == 0) {
        // random
        for (int i = 1; i <= n; i++) {
            H[i] = dist_h(rng);
            W[i] = uniform_int_distribution<int>(1, L)(rng);
        }
    } else if (mode == 1) {
        // large W_i close to L
        for (int i = 1; i <= n; i++) {
            H[i] = dist_h(rng);
            int min_w = max(1, L/2);
            W[i] = uniform_int_distribution<int>(min_w, L)(rng);
        }
    } else if (mode == 2) {
        // very small W_i (but not as small as killer)
        for (int i = 1; i <= n; i++) {
            H[i] = dist_h(rng);
            W[i] = uniform_int_distribution<int>(1, min(10, L))(rng);
        }
    } else if (mode == 3) {
        // monotonic increasing H_i
        int start = uniform_int_distribution<int>(1, 1000)(rng);
        int step = uniform_int_distribution<int>(1, 1000)(rng);
        for (int i = 1; i <= n; i++) {
            H[i] = start + step * (i-1);
            if (H[i] > 1000000000) H[i] = 1000000000;
            W[i] = uniform_int_distribution<int>(1, L)(rng);
        }
    } else if (mode == 4) {
        // monotonic decreasing H_i
        int start = uniform_int_distribution<int>(1, 1000000000)(rng);
        int step = uniform_int_distribution<int>(1, 1000)(rng);
        for (int i = 1; i <= n; i++) {
            H[i] = start - step * (i-1);
            if (H[i] < 1) H[i] = 1;
            W[i] = uniform_int_distribution<int>(1, L)(rng);
        }
    } else if (mode == 5) {
        // random spike heights: mostly small, occasional large
        for (int i = 1; i <= n; i++) {
            if (uniform_int_distribution<int>(1, 100)(rng) <= 90) {
                H[i] = uniform_int_distribution<int>(1, 1000)(rng);
            } else {
                H[i] = 1000000000;
            }
            W[i] = uniform_int_distribution<int>(1, L)(rng);
        }
    } else if (mode == 6) {
        // Killer case 1: decreasing H_i from 1e9 to 1, W_i in [1,5]
        long long decrement = (1000000000LL - 1) / (n - 1);
        long long remainder = (1000000000LL - 1) % (n - 1);

        long long current = 1000000000LL;
        for (int i = 1; i <= n; i++) {
            H[i] = static_cast<int>(current);
            if (H[i] < 1) H[i] = 1;

            if (i <= remainder) {
                current -= (decrement + 1);
            } else {
                current -= decrement;
            }

            W[i] = dist_w_small(rng);
        }
    } else if (mode == 7) {
        // Killer case 2: increasing H_i from 1 to 1e9, W_i in [1,5]
        long long increment = (1000000000LL - 1) / (n - 1);
        long long remainder = (1000000000LL - 1) % (n - 1);

        long long current = 1LL;
        for (int i = 1; i <= n; i++) {
            H[i] = static_cast<int>(current);
            if (H[i] > 1000000000) H[i] = 1000000000;

            if (i <= remainder) {
                current += (increment + 1);
            } else {
                current += increment;
            }

            W[i] = dist_w_small(rng);
        }
    } else if (mode == 8) {
        // Killer case 3: fluctuating H_i (random spikes) with W_i in [1,5]
        for (int i = 1; i <= n; i++) {
            // 95% chance small height (1-1000), 5% chance large height (1e9)
            if (uniform_int_distribution<int>(1, 100)(rng) <= 95) {
                H[i] = uniform_int_distribution<int>(1, 1000)(rng);
            } else {
                H[i] = 1000000000;
            }
            W[i] = dist_w_small(rng);
        }
    }

    // Output
    cout << n << " " << L << "\n";
    for (int i = 1; i <= n; i++) {
        cout << H[i] << " " << W[i] << "\n";
    }

    return 0;
}