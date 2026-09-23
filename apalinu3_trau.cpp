#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
//using namespace __gnu_pbds;
#define LongDepTrai "apalinu3"
#define ll long long
#define ull unsigned long long
#define ld long double
#define ii pair<int,int>
#define iii pair<int,ii>
#define iv pair<ii,ii>
#define pll pair<ll,ll>
#define vi vector<int>
#define vii vector<ii>
#define vll vector<ll>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) int((x).size())
#define order_set(T) tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>

inline ll add(ll a, ll b, ll mod){ a += b; if(a >= mod) a -= mod; return a; }
inline ll sub(ll a, ll b, ll mod){ a -= b; if(a < 0) a += mod; return a; }
inline ll mul(ll a, ll b, ll mod){ return ( (ll)a * b ) % mod; }

static mt19937_64 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());
const int N=3e5+9;
int n,q;
string s[3];
struct node{
    char l,r;
    bool check;
} tree[3][N*4];
node Merge(node a,node b){
    node val;
    if(a.l!='#')
    val.l=a.l;
    if(b.r!='#')
    val.r=b.r;
    val.check=0;
    val.check|=a.check;
    val.check|=b.check;
    if(a.r==b.l) val.check=1;
//    cout<<val.l<<" "<<val.r<<" "<<val.check<<"\n";
    return val;
}
void build(int ty,int i,int l,int r){
    if(l==r){
        tree[ty][i].l=s[ty][l];
        tree[ty][i].r=s[ty][l];
        tree[ty][i].check=0;
        return;

    }

    build(ty,i*2,l,(l+r)/2);
    build(ty,i*2+1,(l+r)/2+1,r);

    tree[ty][i]=Merge(tree[ty][i*2],tree[ty][i*2+1]);
}
void update(int ty,int i,int l,int r,int pos,char c){
    if(l>pos || r<pos) return;
    if(l==r){
        tree[ty][i].l=c;
        tree[ty][i].r=c;
        tree[ty][i].check=0;
        return;
    }
    update(ty,i*2,l,(l+r)/2,pos,c);
    update(ty,i*2+1,(l+r)/2+1,r,pos,c);

    tree[ty][i]=Merge(tree[ty][i*2],tree[ty][i*2+1]);
}
node base;
node get(int ty,int i,int l,int r,int u,int v){
    if(l>v || r<u) return base;
    if(l<=u && v<=r) return tree[ty][i];
    node a=get(ty,i*2,l,r,u,(u+v)/2);
    node b=get(ty,i*2+1,l,r,(u+v)/2+1,v);

    node ans=Merge(a,b);
    return ans;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    if(fopen(LongDepTrai".inp","r")){
        freopen(LongDepTrai".inp","r",stdin);
        freopen(LongDepTrai".ans","w",stdout);
    }
    base.l='#';
    base.r='#';
    base.check=0;

    cin>>n>>q;
    cin>>s[0];
    s[0]=" "+s[0];
    build(0,1,1,n);
    for(int i=1;i<=n;i++){
        if(i%2==1){
            s[1].pb(s[0][i]);
        }
        else{
            s[2].pb(s[0][i]);
        }
    }
    s[1]=" "+s[1];
    s[2]=" "+s[2];
    build(1,1,1,(n+1)/2);
    build(2,1,1,n/2);
//    cout<<s[0]<<"\n"<<s[1]<<"\n"<<s[2]<<"\n";
//    cout<<get(1,1,1,2,1,(n+1)/2).check<<"\n\n";
    while(q--){
        int x,l,r;
        cin>>x>>l>>r;
        if(x==1){
            char sw1=s[0][r];
            char sw2=s[0][l];

            update(0,1,1,n,l,sw1);
            update(0,1,1,n,r,sw2);

            s[0][l]=sw1;
            s[0][r]=sw2;
            if(l%2==0){
                update(2,1,1,n/2,l/2,sw1);
//                s[1][l/2]=sw2;
            }
            else{
                update(1,1,1,(n+1)/2,(l+1)/2,sw1);
            }

            if(r%2==0){
                update(2,1,1,n/2,r/2,sw2);
            }
            else{
                update(1,1,1,(n+1)/2,(r+1)/2,sw2);
            }
        }
        else{
            bool find0=get(0,1,l,r,1,n).check;
            bool find2=get(2,1,(l+1)/2,r/2,1,n/2).check;
            bool find1=get(1,1,min((l+1)/2,(r+1)/2),(r+1)/2,1,(n+1)/2).check;
//            cout<<find0<<" "<<l<<" "<<r<<"\n";
//            cout<<find1<<" "<<(l+2)/2<<" "<<(r+1)/2<<"\n";
//            cout<<find2<<" "<<(l+1)/2<<" "<<r/2<<"\n";
//            cout<<find0<<" "<<find1<<" "<<find2<<"\n";
            cout<<!(find0|find1|find2)<<"\n";
        }
    }

    return 0;
}
