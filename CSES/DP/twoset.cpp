#include<bits/stdc++.h>
using namespace std;

long long mod = 1000000007;
long long dp[70001];

int main(){
    int n; cin>>n;
    long long sum = (1ll*n*(n+1))/2;
    if(sum%2){
        cout<<0<<endl;
        return 0;
    }
    long long target = sum/2;

    dp[0]=1;
    // i<n because as per our logic we are calculating for set not having n, it will be in the opposite set
    for(int i=1;i<n;i++){
        for(int j=target;j>=i;j--){
            dp[j] += dp[j-i];
            dp[j]%=mod;
        }
    }
    cout<<dp[target]<<endl;
    return 0;
}
