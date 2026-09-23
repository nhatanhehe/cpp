#include <bits/stdc++.h>
using namespace std;

bool isPrime(long long x){
    if(x < 2) return false;
    if(x % 2 == 0) return x == 2;
    for(long long i = 3; i * i <= x; i += 2)
        if(x % i == 0) return false;
    return true;
}

long long makePal(long long x, bool odd){
    long long r = x;
    if(odd) x /= 10;
    while(x){
        r = r * 10 + x % 10;
        x /= 10;
    }
    return r;
}

int main(){
    long long n;
    cin >> n;
    cout<<"{";
    for(int len = 1; ; len++){
        for(long long i = pow(10, len-1); i < pow(10, len); i++){
            long long p1 = makePal(i, 1);
            if(p1 > n)
            if(isPrime(p1)) cout << p1 << ",";

            long long p2 = makePal(i, 0);
            if(p2 > n) continue;
            if(isPrime(p2)) cout << p2 << ", ";
        }
    }
    cout<<"}";
}
