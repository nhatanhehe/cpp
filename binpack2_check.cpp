#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int T = inf.readInt();

    for (int tc = 1; tc <= T; tc++) {
        int n = inf.readInt();
        int k = inf.readInt();

        vector<long long> w(n);
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            w[i] = inf.readLong();
            sum += w[i];
        }

        string s = ouf.readToken();

        if ((int)s.size() != n)
            quitf(_wa, "Test %d: output length should be %d", tc, n);

        int cnt0 = 0;
        long long box1 = 0, box2 = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] == '0') cnt0++;
            else if (s[i] == '1') box1 += w[i];
            else if (s[i] == '2') box2 += w[i];
            else
                quitf(_wa, "Test %d: invalid character '%c'", tc, s[i]);
        }

        if (cnt0 != k)
            quitf(_wa,
                  "Test %d: expected %d discarded items, found %d",
                  tc, k, cnt0);

        if (box1 * 2 > sum)
            quitf(_wa,
                  "Test %d: box 1 overweight (%lld > %lld/2)",
                  tc, box1, sum);

        if (box2 * 2 > sum)
            quitf(_wa,
                  "Test %d: box 2 overweight (%lld > %lld/2)",
                  tc, box2, sum);
    }

    if (!ouf.seekEof())
        quitf(_pe, "Extra output");

    quitf(_ok, "Accepted");
}
