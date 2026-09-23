#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 4;
    int L = 10;
    vector<int> H(n+1), W(n+1);

    long long decrement = (1000000000 - 1) / (n - 1);
    long long remainder = (1000000000 - 1) % (n - 1);

    long long current = 1000000000;
    for (int i = 1; i <= n; i++) {
        H[i] = static_cast<int>(current);
        if (H[i] < 1) H[i] = 1;

        if (i <= remainder) {
            current -= (decrement + 1);
        } else {
            current -= decrement;
        }

        W[i] = 1; // fixed for test
    }

    cout << n << " " << L << "\n";
    for (int i = 1; i <= n; i++) {
        cout << H[i] << " " << W[i] << "\n";
    }
    return 0;
}
