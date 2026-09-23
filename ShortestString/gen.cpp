#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <random>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <seed> <n> <max_len>" << endl;
        return 1;
    }
    int seed = atoi(argv[1]);
    int n = atoi(argv[2]);
    int max_len = atoi(argv[3]);

    mt19937 rng(seed);
    uniform_int_distribution<int> char_dist(0, 25); // 'a' to 'z'
    uniform_int_distribution<int> len_dist(1, max_len);
    uniform_int_distribution<int> ov_dist;

    cout << n << endl;
    if (n <= 0) return 0;

    vector<string> strings;

    if (max_len == 1) {
        // generate all strings identical single random char to guarantee overlap
        char c = 'a' + char_dist(rng);
        string s(1, c);
        for (int i = 0; i < n; ++i) {
            strings.push_back(s);
        }
    } else if (n == 1) {
        // single string: random
        int length = max_len;
        string s;
        for (int i = 0; i < length; ++i) {
            s += 'a' + char_dist(rng);
        }
        strings.push_back(s);
    } else {
        // first string random
        int length = max_len;
        string first;
        for (int i = 0; i < length; ++i) {
            first += 'a' + char_dist(rng);
        }
        strings.push_back(first);

        // overlap distribution: 1 to max_len-1
        ov_dist = uniform_int_distribution<int>(1, max_len-1);

        for (int i = 1; i < n; ++i) {
            int overlap = ov_dist(rng);
            // take suffix of previous string of length overlap
            string suffix = strings.back().substr(strings.back().length() - overlap);
            // need to add (max_len - overlap) random chars
            int add_len = max_len - overlap;
            string add;
            for (int j = 0; j < add_len; ++j) {
                add += 'a' + char_dist(rng);
            }
            strings.push_back(suffix + add);
        }
    }

    // shuffle to hide the chain order
    shuffle(strings.begin(), strings.end(), rng);

    for (const string& s : strings) {
        cout << s << endl;
    }
    return 0;
}