#include<bits/stdc++.h>
using namespace std;
#define int long long
#define w first
#define v second
long long U,V,n,maxx=0,o=0;
pair<int,int>a[35],z[65538],q[65538];
int cnt;
int s[35],sv[35],tree[65538*4],g[65538],j[65538],tree1[65538*4];
void build(int id,int l,int r){
    if(l==r){
        tree[id]=q[l].v;
        return;
    }
    int mid=(l+r)/2;
    build(id*2,l,mid);
    build(id*2+1,mid+1,r);
    tree[id]=max(tree[id*2],tree[id*2+1]);
}
int get(int id,int l,int r,int u,int v){
    if(l>v||r<u) return -1;
    if(u<=l&&r<=v) return tree[id];
    int mid=(l+r)/2;
    return max(get(id*2,l,mid,u,v),get(id*2+1,mid+1,r,u,v));
}
void ql(int i,int w,int v,int k){
    if(w>V) return;
    if(i>k){
        z[++o].w=w;
        z[o].v=v;
        return;
    }
    ql(i+1,w,v,k);
    ql(i+1,w+a[i].w,v+a[i].v,k);
}
void ql2(int i,int w,int v){
    if(w>V) return;
    if(i>n){
        q[++o].w=w;
        q[o].v=v;
        return;
    }
    ql2(i+1,w,v);
    ql2(i+1,w+a[i].w,v+a[i].v);
}
main(){
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
       cout.tie(NULL);
if(fopen("a.inp","r")){
     freopen("a.inp","r",stdin);
     freopen("a.out","w",stdout);
}
    cin>>n>>U>>V;
    for(int i=1;i<=n;i++){
        cin>>a[i].w>>a[i].v;
    }
    int k=n/2;
    ql(1,0,0,k);
    int p=o;
    o=0;
    ql2(k+1,0,0);
    sort(q+1,q+o+1);
    build(1,1,o);
    //for(int i=1;i<=o;i++) cout<<q[i].w<<" "<<q[i].v<<'\n'; cout<<'\n';
    for(int i=1;i<=o;i++){
        g[i]=q[i].w;
    }
    for(int i=1;i<=p;i++){
        int l=lower_bound(g+1,g+o+1,U-z[i].w)-g;
        int r=upper_bound(g+1,g+o+1,V-z[i].w)-g-1;
        int val=get(1,1,o,l,r);
        if(val==-1) continue;
        maxx=max(maxx,z[i].v+val);
    }
    cout<<maxx;
}

