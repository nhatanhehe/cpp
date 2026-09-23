#include<bits/stdc++.h>
#include "abcards.h"
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define debug(x) cout<< #x << " = "<< x <<'\n'
#define Task "a"
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf=1e18;
const ll N=2e5+5;
const ll mod=1e9+7;
const ll base=311;
const ll phainon=33550336;
#define On(mask,i) (mask|(1LL<<i))
#define Off(mask,i) (mask&~(1LL<<i))

namespace personA {
    ll C[60][30];
void cal(){
    for(int i=0;i<=52;i++){
        C[i][0]=1;
        for(int j=1;j<=min(i,20);j++){
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
}
    long long A2B(vector<int>c){
    cal();
    sort(all(c));
    int n=52;
    int k=c.size();
    ll rnk=1;
    for(int i=1;i<k;i++){
        rnk+=C[n][i];
    }
    int pre=0;
    for(int i=1;i<=k;i++){
        for(int j=pre+1;j<c[i-1];j++){
            rnk+=C[n-j][k-i];
        }
        pre=c[i-1];
    }
    return rnk;
}
}

namespace personB {
    ll C[60][30];
void cal(){
    for(int i=0;i<=52;i++){
        C[i][0]=1;
        for(int j=1;j<=min(i,20);j++){
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
}
    vector<int> Btell(long long _Num){
        cal();
        int n=52;
        int k;
        for(int i=1;i<=20;i++){
            if(_Num>C[n][i]) _Num-=C[n][i];
            else{
                k=i;
                break;
            }
        }
        vector<int>ans;
        int pre=0;
        for(int i=1;i<=k;i++){
            for(int j=pre+1;j<=n;j++){
                ll tmp=C[n-j][k-i];
                if(_Num>tmp) _Num-=tmp;
                else{
                    ans.pb(j);
                    pre=j;
                    break;
                }

            }
        }
        return ans;
    }
}
