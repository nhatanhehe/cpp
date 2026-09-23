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

    // For biased generation towards higher lexicographic order
    // We'll pick n and k towards the upper end of the allowed range
    uniform_int_distribution<int> dist_k(1, k_max);
    int k = dist_k(rng);
    // bias k towards higher values
    if (rng() % 3 != 0) { // 2/3 of the time, bias upwards
        k = min(k_max, k + k_max / 4);
    }

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
    // bias pairs towards higher values
    if (rng() % 3 != 0) { // 2/3 of the time, bias upwards
        pairs = min(max_n/2, pairs + (max_n/2 - min_n/2) / 4);
    }
    int n = pairs * 2;

    // generate bracket sequence with bias towards higher lexicographic order
    string res;
    res.reserve(n);
    int open = 0; // number of '(' placed
    int close = 0; // number of ')' placed
    // stack for expected closing chars
    vector<char> st;
    st.reserve(n/2);

    // Bracket types in lexicographic order: ( ) [ ] { }
    // For opening brackets, we want to prefer {, then [, then ( for higher lexicographic order
    // For closing brackets, we want to prefer }, then ], then ) for higher lexicographic order
    const string opening = "({["; // Note: reversed for ease of indexing - we'll use indices 2,1,0
    const string closing = "])}"; // Note: reversed for ease of indexing - we'll use indices 2,1,0
    // Actually, let's keep them in order and define preference arrays
    const char opening_brackets[] = {'(', '[', '{'}; // increasing lexicographic order
    const char closing_brackets[] = {')', ']', '}'}; // increasing lexicographic order
    // For bias towards HIGHER lexicographic order, we prefer indices 2,1,0 (descending)

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
        else {
            // Both options possible - use bias for lexicographic order
            // We'll look ahead a bit to see which choice might lead to higher lexicographic order
            // Simple heuristic:
            // - If we can open with '{' (highest opening), strongly prefer opening
            // - If we must close with '}' (highest closing), consider closing
            // - Otherwise, use some randomness with bias

            // What would be the best opening we could place?
            int best_open_type = -1;
            for (int t = 2; t >= 0; --t) { // try {, [, ( in that order (highest to lowest)
                if (t == 0 && open < n/2) { best_open_type = t; break; } // Actually all types have same count limit
                // All opening types use one "open" slot, so the limit is the same for all
                if (open < n/2) { best_open_type = t; break; }
            }

            // What would be the closing we MUST place if we choose to close?
            int close_type_index = -1;
            if (!st.empty()) {
                char expected = st.back();
                if (expected == '(') close_type_index = 0;
                else if (expected == '[') close_type_index = 1;
                else if (expected == '{') close_type_index = 2;
            }

            // Bias decision:
            // Prefer opening if we can place a high lexicographic opening bracket
            // Prefer closing if we must place a high lexicographic closing bracket

            bool prefer_open = false;
            bool prefer_close = false;

            if (best_open_type >= 0) {
                // We can place an opening bracket
                // Prefer it if it's a high lexicographic one ({ or [)
                if (best_open_type >= 1) { // [ or {
                    prefer_open = true;
                }
            }

            if (close_type_index >= 0) {
                // We would need to place a specific closing bracket
                // Prefer closing if it's a high lexicographic one (} or ])
                if (close_type_index >= 1) { // ] or }
                    prefer_close = true;
                }
            }

            if (prefer_open && !prefer_close) {
                choose_open = true;
            } else if (prefer_close && !prefer_open) {
                choose_open = false;
            } else {
                // Either both preferred, neither preferred, or conflict
                // Use biased randomness: 2/3 chance to open (to get more opening brackets which can be high lexicographic)
                choose_open = (rng() % 3 != 0);
            }
        }

        if (choose_open) {
            // Choose opening bracket type with bias towards higher lexicographic order
            // preference: { (index 2), [ (index 1), ( (index 0)
            int type_weights[] = {1, 2, 4}; // weights for (, [, { - higher weight for lexicographically larger
            int total_weight = type_weights[0] + type_weights[1] + type_weights[2];
            int r = rng() % total_weight;
            int type;
            if (r < type_weights[0]) {
                type = 0; // (
            } else if (r < type_weights[0] + type_weights[1]) {
                type = 1; // [
            } else {
                type = 2; // {
            }

            char op = opening_brackets[type];
            char cl;
            if (type == 0) { cl = ')'; }
            else if (type == 1) { cl = ']'; }
            else { cl = '}'; }

            res.push_back(op);
            st.push_back(cl);
            ++open;
        } else {
            // Must close - the type is forced by what's on top of stack
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