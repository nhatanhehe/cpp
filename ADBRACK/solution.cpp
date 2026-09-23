#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

long long dp[101][51]; // dp[remaining][height] = number of ways

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    string s;
    if (!(cin >> n >> k)) return 0;
    cin >> s;

    // k might be given larger than n/2 due to input, but constraint says 2*k <= n
    k = min(k, n/2);

    // Initialize dp
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int rem = 1; rem <= n; ++rem) {
        for (int h = 0; h <= k; ++h) {
            long long val = 0;
            // place an opening bracket: 3 types
            if (h < k) {
                val = (val + 3 * dp[rem-1][h+1]) % MOD;
            }
            // place a closing bracket: only 1 type (forced by matching open)
            if (h > 0) {
                val = (val + dp[rem-1][h-1]) % MOD;
            }
            dp[rem][h] = val;
        }
    }

    long long rank = 0; // 0-indexed rank, will output rank+1
    vector<char> st; // stack for validation
    int height = 0;

    const string brackets = "()[]{}";
    // order: index 0:'(', 1:')', 2:'[', 3:']', 4:'{', 5:'}'

    for (int i = 0; i < n; ++i) {
        char target = s[i];
        for (char c : brackets) {
            if (c == target) {
                // fix this character and move on
                if (c == '(' || c == '[' || c == '{') {
                    st.push_back(c);
                    ++height;
                } else {
                    // closing bracket
                    if (st.empty()) {
                        // should not happen for valid s
                        cout << 0 << '\n';
                        return 0;
                    }
                    char expected;
                    if (st.back() == '(') expected = ')';
                    else if (st.back() == '[') expected = ']';
                    else if (st.back() == '{') expected = '}';
                    if (c != expected) {
                        // invalid sequence, but guaranteed valid
                        cout << 0 << '\n';
                        return 0;
                    }
                    st.pop_back();
                    --height;
                }
                break;
            }
            // consider placing c instead of target
            bool can_place = false;
            int new_height = height;
            if (c == '(' || c == '[' || c == '{') {
                // opening
                if (height < k) {
                    can_place = true;
                    new_height = height + 1;
                }
            } else {
                // closing
                if (height > 0) {
                    // need to check if c matches the expected closing for current stack top
                    char expected;
                    if (st.empty()) { can_place = false; }
                    else {
                        if (st.back() == '(') expected = ')';
                        else if (st.back() == '[') expected = ']';
                        else if (st.back() == '{') expected = '}';
                        if (c == expected) {
                            can_place = true;
                            new_height = height - 1;
                        }
                    }
                }
            }
            if (can_place) {
                // number of ways to complete the remaining positions
                int rem = n - i - 1;
                rank = (rank + dp[rem][new_height]) % MOD;
            }
        }
    }

    // rank is 0-indexed, answer is rank+1
    cout << (rank + 1) % MOD << '\n';
    return 0;
}
