#include<bits/stdc++.h>
using namespace std;
// int |x| <= 2.000.000.000
// long long |x| <= 2*10^18
// + cong
// - tru
// * nhan
// / chia 7/2=3.5, 7/2 = 3
// % chia lay du 7%2
// float, long double: có tác dụng là lưu số thực 3.0,3.7,6.736
main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    float T;
    cin>>T; ///yeu cau may tinh cung cap gia tri cua T
    //T=5.0
    if(T>=9.0) cout<<"VERY TOXIC";
    if(T>=5.0 && T<=8.9) cout<<"TOXIC";
    if(T<=5.0) cout<<"SAFE"; //=> TOXICSAFE
}
