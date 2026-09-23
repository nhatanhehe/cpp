#include<bits/stdc++.h>
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
const int inf=1e18;
const int N=10005;
const int mod=1e9+7;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int add(int a,int b){
    int res=a+b;
    if(res>=mod) res-=mod;
    return res;
}

inline int sub(int a,int b){
    return ((a-b)%mod+mod)%mod;
}

string a,b;
int q;
ll dp[N][9][2][32];
ll calc(int i,int md,bool lo,bool lead,int mask,string &s){
    if(i==-1){
        if(!lead && (md==3 || md==6)) return 1;
        return 0;
    }

    ll &ans=dp[i][md][lead][mask];
    if(lo&&ans!=-1) return ans;
    ll res=0;
    int limit=lo?9:(s[i]-'0');

    for(int j=0;j<=limit;j++){
        bool nxt_tight=lo||(j<limit);

        if(lead && j==0){
            res=add(res,calc(i-1,0,nxt_tight,true,0,s));
        }else{
            bool ok=true;
            int nxt_mask=mask;

            if(j==0 || j==5){
                if(mask&(1<<0)) ok=false;
                nxt_mask|=(1<<0);
            }else if(j==1 || j==6){
                if(mask&(1<<2)) ok=false;
                nxt_mask|=(1<<1);
            }else if(j==4 || j==9){
                if(mask&(1<<1)) ok=false;
                nxt_mask|=(1<<2);
            }else if(j==2 || j==7){
                if(mask&(1<<4)) ok=false;
                nxt_mask|=(1<<3);
            }else if(j==3 || j==8){
                if(mask&(1<<3)) ok=false;
                nxt_mask|=(1<<4);
            }

            if(ok){
                res=add(res,calc(i-1,(md+j)%9,nxt_tight,false,nxt_mask,s));
            }
        }
    }

    return lo? ans=res:res;
}

void decrease(string &s){
    int i=s.size()-1;
    while(i>=0 && s[i]=='0'){
        s[i]='9';
        i--;
    }
    if(i>=0) s[i]--;

    int pos=0;
    while(pos+1<s.size() && s[pos]=='0') pos++;
    s.erase(0,pos);
}

ll solve(string s){
    int len=s.size();
    reverse(all(s));
    return calc(s.size()-1,0,false,true,0,s);
}
bool check(ll n){
    if(n<=0) return false;
    if(n%3!=0||n%9==0) return false;
    bool cnt[10]={0};
    while(n){
        int x=n%10;
        for(int i=0;i<10;i++){
            if(cnt[i]&&(i+x)%5==0) return false;
        }
        cnt[x]=1;
        n/=10;
    }
    return true;
}
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    if(fopen(Task ".inp","r")){
        freopen(Task ".inp","r",stdin);
        freopen(Task ".out","w",stdout);
    }

    cin>>q;
    if(q>100){
        vector<int>pre(1000005,0);
        for(int i=1;i<=1e5;i++){
            pre[i]=pre[i-1]+check(i);
        }
        while(q--){
            int l,r;
            cin>>l>>r;
            cout<<pre[r]-pre[l-1]<<'\n';
        }
        return 0;
    }
    memset(dp,-1,sizeof dp);
    while(q--){
        cin>>a>>b;
        if(a!="0") decrease(a);

        ll ansB=solve(b);
        ll ansA=(a=="0")?0:solve(a);

        cout<<sub(ansB,ansA)<<'\n';
    }

    return 0;
}
