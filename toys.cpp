#include<bits/stdc++.h>
using namespace std;

#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define debug(x) cout<< #x << " = "<< x <<'\n'
#define Task "toys"
#define ii pair<int,int>
#define iii pair<ii,int>
#define all(x) x.begin(),x.end()
#define fi first
#define se second

const ll inf=1e18;
const int N=1e5+5;
const ll mod=1e9+7;

ll add(ll x,ll y){return (x+y)%mod;}
ll sub(ll x,ll y){return (x-y+mod)%mod;}
ll mul(ll x,ll y){return (x*y)%mod;}

ll power(ll x,ll y){
    if(y==0) return 1;
    ll tmp=power(x,y/2);
    if(y%2==0) return tmp*tmp%mod;
    return tmp*tmp%mod*x%mod;
}

int n;
string s;
int cnt[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    if(fopen(Task".inp","r")){
        freopen(Task".inp","r",stdin);
        freopen(Task".out","w",stdout);
    }

    cin>>n>>s;

    ll mn=1e9, min_len=1;
    int ansl, ansr;

    for(int k=1;k<=26;k++){
        for(int i=0;i<26;i++) cnt[i]=0;

        int d=0,l=0;

        for(int r=0;r<n;r++){
            if(cnt[s[r]-'a']==0) d++;
            cnt[s[r]-'a']++;

            while(d>k){
                cnt[s[l]-'a']--;
                if(cnt[s[l]-'a']==0) d--;
                l++;
            }

            int tmp=d;
            int len=r-l+1;

            if(tmp*min_len<mn*len){
                mn=tmp;
                min_len=len;
                ansl=l;
                ansr=r;
            }
            else if(tmp*min_len==mn*len){
                if(l+1<ansl){
                    ansl=l+1;
                    ansr=r+1;
                }
            }
        }
    }

    cout<<ansl+1<<" "<<ansr+1;

}