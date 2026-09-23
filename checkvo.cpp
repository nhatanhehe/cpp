#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int m = inf.readInt();
    int n = inf.readInt();

    vector<long long> a(m + 1), b(n + 1);

    for (int i = 1; i <= m; i++) a[i] = inf.readLong();
    for (int i = 1; i <= n; i++) b[i] = inf.readLong();

    auto check = [&](InStream &s) -> bool {
        string t = upperCase(s.readWord());

        if (t == "no") {
            s.readWord(); // Volleyball
            s.readWord(); // Today
            return false;
        }

        int i = stoi(t);
        int j = s.readInt();
        int u = s.readInt();
        int v = s.readInt();

        if (!(1 <= i && i <= m &&
              1 <= j && j <= m &&
              1 <= u && u <= n &&
              1 <= v && v <= n))
            s.quitf(_wa, "Index out of range");

        if (i == j || u == v)
            s.quitf(_wa, "Indices must be distinct");

        return a[i] + a[j] == b[u] + b[v];
    };

    bool jury = check(ans);
    bool cont = check(ouf);

    if (jury && !cont)
        quitf(_wa, "Solution exists but contestant failed");

    if (!jury && cont)
        quitf(_fail, "Contestant found a solution but jury says none");

    if (!jury && !cont)
        quitf(_ok, "No solution");

    quitf(_ok, "Correct");
}
