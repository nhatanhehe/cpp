#include <bits/stdc++.h>
using namespace std;
#define int long long
// Tên chương trình
const string NAME = "flappy";
// Số test kiểm tra
const int NTEST = 30;

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

// Viết lại hàm random để sử dụng cho thuận tiện.
// Hàm random này sinh ngẫu nhiên số trong phạm vi long long
// Số sinh ra nằm trong [L;R].
long long Rand(long long L, long long R) {
    return uniform_int_distribution<int>(L,R)(rd);
}

main()
{
    srand(time(NULL));
    for (int iTest = 1; iTest <= NTEST; iTest++)
    {
        ofstream inp(("a.inp"));
        int n=1e5,q=1e5;
        inp<<n<<" "<<q<<'\n';
        inp<<1000000000<<'\n';
        for(int i=2;i<=n;i++){
            inp<<Rand(1,1e9)<<" ";
        }
        inp.close();
        // Nếu dùng Linux thì "./" + Tên chương trình
        system((NAME + ".exe").c_str());
        system((NAME + "_trau.exe").c_str());
        // Nếu dùng linux thì thay fc bằng diff
        if (system(("fc  a.out a.ans")) != 0)
        {
            cout << "Test " << iTest << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << iTest << ": CORRECT!\n";
    }
    return 0;
}

