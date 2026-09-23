#include<bits/stdc++.h>
using namespace std;
const int N=3e4+6;
long long n,a[10004],temps,k,tong=0,ans,l=0;
int sgpbangg=0;
bool dp[1003][N];
long long z[2000007];
void firsttry(int i,long long sum){
    if(i>k){
        z[++sgpbangg]= sum;
        return;
    }
    firsttry(i+1,sum);
    firsttry(i+1,sum+a[i]);
}
void sectry(int i,long long sum){
    if(i>n){
        ans=min({abs(l-z[upper_bound(z+1,z+sgpbangg+1,tong-sum)-z-1]-sum-z[upper_bound(z+1,z+sgpbangg+1,tong-sum)-z-1]-sum),abs(l-z[lower_bound(z+1,z+sgpbangg+1,tong-sum)-z]-sum-z[lower_bound(z+1,z+sgpbangg+1,tong-sum)-z]-sum),ans});
        return;
    }
    sectry(i+1,sum);
    sectry(i+1,sum+a[i]);
}
void qhd(){
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=l;j++){
            if(a[i]<=j&&(dp[i-1][j-a[i]]||dp[i-1][j])) dp[i][j]=1;
            else dp[i][j]=0;
        }
    }
    int e=0;
    for(int j=1;j<=l;j++){
        //cout<<dp[n][j]<<" "<<j<<'\n';
        if(dp[n][j]&&j<=tong) e=j;
    }
    cout<<abs(l-2*e);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
       cout.tie(NULL);
     // freopen("candy.inp","r",stdin);
   //   freopen("candy.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        tong+=a[i];
        l+=a[i];
    }
    tong/=2;
    k=n/2;
    sgpbangg=0;
    if(n<=40){
    firsttry(1,0);
    ans=LLONG_MAX;
    sort(z+1,z+sgpbangg+1);
    sectry(k+1,0);
    cout<<ans;
    }
    else qhd();
}

