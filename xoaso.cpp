#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define Task "XOASO"
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf=1e18;
const ll mod=3;
const ll N=1e5+5;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if(fopen(Task".INP","r")){
        freopen(Task".INP","r",stdin);
        freopen(Task".OUT","w",stdout);
    }
    string s;cin>>s;
    int n=s.size();
    vector<int> pre(n+1,0);
    for(int i=1;i<=n;i++)pre[i]=(pre[i-1]+(s[i-1]-'0'))%3;
    int tg=pre[n];
    ll cntSuffix[3]={0,0,0};
    for(int j=1;j<=n;j++)cntSuffix[pre[j]]++;
    ll cnt_nonempty=0;
    for(int i=0;i<=n-1;i++){
        int need=(pre[i]+tg)%3;
        cnt_nonempty+=cntSuffix[need];
        if(i+1<=n)cntSuffix[pre[i+1]]--;
    }
    ll cnt_empty=(tg==0)?1:0;
    ll result=cnt_nonempty+cnt_empty-1;
    cout<<result;
}
