#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define debug(x) cout<< #x << " = " << x << '\n'
#define Task "BSHOP"
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
const ll inf=1e18;
const int N=1e5+5;
int n,q;
ii a[N];
int st[4*N];
void build(int id,int l,int r){
    if(l==r){
        st[id]=a[l].se;
        return;
    }
    int mid=(l+r)/2;
    build(id*2,l,mid);
    build(id*2+1,mid+1,r);
    st[id]=max(st[id*2],st[id*2+1]);
}
int get(int id,int l,int r,int u,int v){
    if(v<l||r<u) return 0;
    if(u<=l&&r<=v) return st[id];
    int mid=(l+r)/2;
    return max(get(id*2,l,mid,u,v),get(id*2+1,mid+1,r,u,v));
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if(fopen(Task ".inp","r")){
        freopen(Task ".inp","r",stdin);
        freopen(Task ".out","w",stdout);
    }
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].fi>>a[i].se;
    sort(a+1,a+n+1);
    build(1,1,n);
    vector<int> price(n+1);
    for(int i=1;i<=n;i++) price[i]=a[i].fi;
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        int l=lower_bound(price.begin()+1,price.end(),x)-price.begin();
        int r=upper_bound(price.begin()+1,price.end(),y)-price.begin()-1;
        if(l>r) cout<<0<<'\n';
        else cout<<get(1,1,n,l,r)<<'\n';
    }
    return 0;
}