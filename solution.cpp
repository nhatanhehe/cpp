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
const ll inf=1e18;
const ll N=2e5+5;
const ll mod=1e9+7;
const ll base=311;
const ll phainon=33550336;
#define On(mask,i) (mask|(1LL<<i))
#define Off(mask,i) (mask&~(1LL<<i))
inline ll add(ll a,ll b){
    ll res=a+b;
    if(res>=mod) res-=mod;
    return res;
}
ll sub(ll a,ll b){
    return ((a-b)%mod+mod)%mod;
}
inline ll mul(ll a,ll b){
    ll res=a*b;
    if(res>=mod) res%=mod;
    return res;
}
bool maximize(int &a,int b){
    if(b<0) return 0;
    if(a<b){
        a=b;
        return 1;
    }
    return 0;
}
int n,q,a[N],v[10][10],dp[4][4][N][4][4],mx[4][4][4],tree[N*4][4][4];
ii lz[N<<2];
void merge(int id){
    for(int _x=1;_x<=3;_x++){
        for(int _y=1;_y<=3;_y++){
            tree[id][_x][_y]=-1e9;
        }
    }
    for(int x=1;x<=3;x++){
        for(int y=1;y<=3;y++){
            if(tree[id*2][x][y]!=-1e9){
                for(int a=1;a<=3;a++){
                    for(int b=1;b<=3;b++){
                        if(tree[id*2+1][a][b]!=-1e9&&v[y][a]){
                            maximize(tree[id][x][b],tree[id*2][x][y]+tree[id*2+1][a][b]);
                        }
                    }
                }
            }
        }
    }
}
void apply(int id,int x,int y,int len){
    for(int _x=1;_x<=3;_x++){
        for(int _y=1;_y<=3;_y++){
            tree[id][_x][_y]=dp[x][y][len][_x][_y];
        }
    }
    lz[id].fi=x;
    lz[id].se=y;
}
void push(int id,int l,int r){
    if(lz[id]!=ii(-1,-1)){
        auto [x,y]=lz[id];
        int mid=(l+r)>>1;
        apply(id*2,x,y,mid-l+1);
        apply(id*2+1,(x+(mid-l+1)*y)%4,y,r-mid);
    }
    lz[id]=ii(-1,-1);
}
void build(int id=1,int l=1,int r=n){
    if(l==r){
        if(a[l]){
            tree[id][a[l]][a[l]]=a[l];
        }
        else{
            for(int x=1;x<=3;x++){
                tree[id][x][x]=x;
            }
        }
        return;
    }
    int mid=(l+r)>>1;
    build(id*2,l,mid);
    build(id*2+1,mid+1,r);
    merge(id);
}
void up(int u,int v,int x,int y,int id=1,int l=1,int r=n){
    if(l>v||r<u) return;
    if(u<=l&&r<=v){
        apply(id,(x+(l-u)*y)%4,y,r-l+1);
        return;
    }
    push(id,l,r);
    int mid=(l+r)>>1;
    up(u,v,x,y,id*2,l,mid);
    up(u,v,x,y,id*2+1,mid+1,r);
    merge(id);
}
int get(){
    int mx=-1;
    for(int x=1;x<=3;x++){
        for(int y=1;y<=3;y++){
            mx=max(mx,tree[1][x][y]);
        }
    }
    return mx;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin>>n>>q;
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++){
            cin>>v[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=4*n+2;i++){
        for(int x=1;x<=3;x++){
            for(int y=1;y<=3;y++){
                tree[i][x][y]=-1e9;
            }
        }
        lz[i]=ii(-1,-1);
    }
    for(int x=0;x<=3;x++){
        for(int y=0;y<=3;y++){
            for(int i=1;i<=n;i++){
                for(int _x=1;_x<=3;_x++){
                    for(int _y=1;_y<=3;_y++){
                        dp[x][y][i][_x][_y]=-1e9;
                    }
                }
            }
        }
    }
    for(int x=0;x<=3;x++){
        for(int y=0;y<=3;y++){
            if(x==0){
                for(int s=1;s<=3;s++){
                    dp[x][y][1][s][s]=s;
                }
            }
            else dp[x][y][1][x][x]=x;
            for(int s=1;s<=3;s++){
                for(int i=2;i<=n;i++){
                    int num=(x+(i-1)*y)%4;
                    if(!num){
                        for(int _x=1;_x<=3;_x++){
                            for(int _y=1;_y<=3;_y++){
                                if(v[_x][_y]&&dp[x][y][i-1][s][_x]!=-1e9)
                                    maximize(dp[x][y][i][s][_y],dp[x][y][i-1][s][_x]+_y);
                            }
                        }
                    }
                    else{
                        for(int _x=1;_x<=3;_x++){
                            if(v[_x][num]&&dp[x][y][i-1][s][_x]!=-1e9)
                                maximize(dp[x][y][i][s][num],dp[x][y][i-1][s][_x]+num);
                        }
                    }
                }
            }
        }
    }
    build();
    cout<<get()<<'\n';
    while(q--){
        int x,y,l,r;
        cin>>l>>r>>x>>y;
        up(l,r,x,y);
        cout<<get()<<'\n';
    }
    return 0;
}