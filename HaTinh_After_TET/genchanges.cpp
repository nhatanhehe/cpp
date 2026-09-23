#include<bits/stdc++.h>
#define ll long long
using namespace std;

const string NAME = "a";
const string NAME2 = "CHANGES2";
const int Test = 1000;

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

ll Rand(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rd);
}

int main() {
    for(int t = 1; t <= Test; t++) {

        ofstream inp("a.inp");

        // ======== Sinh dữ liệu =========

        int c = Rand(1e5, 5e5);       // chỉnh lại nếu cần
        int n = Rand(c, c
                     );

        inp << c << " " << n << "\n";

        for(int i = 1; i <= n; i++) {
            int val = Rand(1, c);   // giá trị xu <= c
            inp << val << " ";
        }

        inp << "\n";
        inp.close();

        // ======== Chạy 2 chương trình ========

        system("main.exe");
        system("main_trau.exe");

        // ======== So sánh kết quả ========

        if(system("fc a.out a.ans") != 0) {
            cout << "Test " << t << " WRONG\n";
            return 0;
        } else {
            cout << "Test " << t << " CORRECT\n";
        }
    }
}
