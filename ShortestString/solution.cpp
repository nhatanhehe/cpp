#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int getOverlap(const string& a, const string& b) {
    int max_ov = 0;
    int limit = min(a.length(), b.length());
    for (int i = 1; i <= limit; ++i) {
        if (a.substr(a.length() - i) == b.substr(0, i)) {
            max_ov = i;
        }
    }
    return max_ov;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<string> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    vector<string> filtered;
    for (int i = 0; i < n; ++i) {
        bool is_substr = false;
        for (int j = 0; j < n; ++j) {
            if (i != j && s[j].find(s[i]) != string::npos) {
                if (s[i].length() < s[j].length() || (s[i].length() == s[j].length() && i > j)) {
                    is_substr = true;
                    break;
                }
            }
        }
        if (!is_substr) {
            filtered.push_back(s[i]);
        }
    }
    s = filtered;

    while (s.size() > 1) {
        int max_ov = -1;
        int merge_i = -1, merge_j = -1;

        for (int i = 0; i < s.size(); ++i) {
            for (int j = 0; j < s.size(); ++j) {
                if (i != j) {
                    int ov = getOverlap(s[i], s[j]);
                    if (ov > max_ov) {
                        max_ov = ov;
                        merge_i = i;
                        merge_j = j;
                    }
                }
            }
        }
        string merged = s[merge_i] + s[merge_j].substr(max_ov);

        vector<string> next_s;
        for (int i = 0; i < s.size(); ++i) {
            if (i != merge_i && i != merge_j) {
                next_s.push_back(s[i]);
            }
        }
        next_s.push_back(merged);
        s = next_s;
    }

    cout << s[0] << "\n";
    return 0;
}