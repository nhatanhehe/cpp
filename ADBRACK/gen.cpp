#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    int seed = 1;
    int n_max = 10;
    int k_max = 10;
    if (argc >= 2) seed = stoi(argv[1]);
    if (argc >= 3) n_max = stoi(argv[2]);
    if (argc >= 4) k_max = stoi(argv[3]);

    mt19937 rng(seed);
    // adjust k_max so that 2*k_max <= n_max
    int max_k_possible = n_max / 2;
    if (k_max > max_k_possible) k_max = max_k_possible;
    if (k_max < 1) k_max = 1;

    uniform_int_distribution<int> dist_k(1, k_max);
    int k = dist_k(rng);
    // n must be even, at least 2*k, at most n_max
    int min_n = 2 * k;
    int max_n = n_max;
    // ensure max_n is even
    if (max_n % 2 != 0) max_n--;
    if (min_n > max_n) {
        // fallback: set n = min_n (make even)
        min_n = (min_n / 2) * 2;
        max_n = min_n;
    }
    uniform_int_distribution<int> dist_n(min_n/2, max_n/2); // random number of pairs
    int pairs = dist_n(rng);
    int n = pairs * 2;

    // generate bracket sequence with depth <= k
    string res;
    res.reserve(n);
    int open = 0; // number of '(' placed
    int close = 0; // number of ')' placed
    // stack for expected closing chars
    vector<char> st;
    st.reserve(n/2);

    while (static_cast<int>(res.size()) < n) {
        bool can_open = (open < n/2) && ((open - close) < k);
        bool can_close = (close < open);
        if (!can_open && !can_close) {
            // should not happen
            cerr << "Generation stuck\n";
            return 1;
        }
        bool choose_open;
        if (!can_open) choose_open = false;
        else if (!can_close) choose_open = true;
        else choose_open = (rng() & 1);
        if (choose_open) {
            // choose a random bracket type
            uniform_int_distribution<int> dist_type(0, 2);
            int t = dist_type(rng);
            char op;
            char cl;
            if (t == 0) { op = '('; cl = ')'; }
            else if (t == 1) { op = '['; cl = ']'; }
            else { op = '{'; cl = '}'; }
            res.push_back(op);
            st.push_back(cl);
            ++open;
        } else {
            // must close
            char cl = st.back();
            st.pop_back();
            res.push_back(cl);
            ++close;
        }
    }
    // sanity check
    assert(open == n/2 && close == n/2);
    assert(st.empty());

    cout << n << ' ' << k << '\n';
    cout << res << '\n';
    return 0;
}