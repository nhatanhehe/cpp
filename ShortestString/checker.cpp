#include "testlib.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    setName("checker for Shortest Superstring");
    registerTestlibCmd(argc, argv);

    // Read input: first integer n, then n strings
    int n = inf.readInt();
    vector<string> patterns;
    for (int i = 0; i < n; ++i) {
        patterns.push_back(inf.readString());
    }

    // Read jury answer (from ans)
    string ans_str = ans.readString();
    // Read participant answer (from ouf)
    string ouf_str = ouf.readString();

    // Verify that ouf contains each pattern as a substring
    for (const string& pat : patterns) {
        if (ouf_str.find(pat) == string::npos) {
            quitf(_wa, "Answer does not contain substring \"%s\"", pat.c_str());
        }
    }

    int Y = (int)ans_str.length();
    int X = (int)ouf_str.length();

    // Ensure Y is not zero (should not happen by constraints)
    if (Y == 0) {
        quitf(_wa, "Jury answer is empty");
    }

    double ratio = (double)X / Y;

    if (X <= Y) {
        quitp(1.0, "OK");
    } else if (ratio <= 1.5) {
        double score = pow((3.0 - 2.0 * ratio), 3.0);
        quitp(score, "OK");
    } else {
        quitp(0.0, "OK");
    }
}