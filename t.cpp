#include<bits/stdc++.h>
using namespace std;

int main ()
{
    long double a , b ;
    cin>>a>>b;
    long long m=a , c=b ;
    //TH1  a=6 neu ma dat m=a, m=6
    //TH2 a=6.76767 neu dat m=a, m=6

    cout<<fixed<<setprecision(3)<<a/b;

    cout<<'\n';
    cout<<m%c<<'\n';
    cout<<m/c;

    return 0;




}
