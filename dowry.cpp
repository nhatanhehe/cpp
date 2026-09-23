#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ii pair<int,int>
#define w first
#define v second
long long U,V,n,maxx=0,o=0;
pair<int,int>a[35],z[65538],q[65538];
int cnt;
int s[35],sv[35],g[65538],j[65538],tree1[65538*4];
ii tree[65538*4];
void build(int id,int l,int r){
    if(l==r){
        tree[id]=ii(q[l].v,q[l].w);
        return;
    }
    int mid=(l+r)/2;
    build(id*2,l,mid);
    build(id*2+1,mid+1,r);
    tree[id]=max(tree[id*2],tree[id*2+1]);
}
ii get(int id,int l,int r,int u,int v){
    if(l>v||r<u) return ii(-1,-1);
    if(u<=l&&r<=v) return tree[id];
    int mid=(l+r)/2;
    return max(get(id*2,l,mid,u,v),get(id*2+1,mid+1,r,u,v));
}
map<ii,vector<int>>it1,it2;
void ql(int i,int w,int v,int k,vector<int>items){
    if(w>V) return;
    if(i>k){
        z[++o].w=w;
        z[o].v=v;
        if(it1.find(ii(w,v))==it1.end()){
            it1[ii(w,v)]=items;
        }
        return;
    }
    ql(i+1,w,v,k,items);
    vector<int>tmp=items;
    tmp.pb(i);
    ql(i+1,w+a[i].w,v+a[i].v,k,tmp);
}
void ql2(int i,int w,int v,vector<int>items){
    if(w>V) return;
    if(i>n){
        q[++o].w=w;
        q[o].v=v;
        if(it2.find(ii(w,v))==it2.end()){
            it2[ii(w,v)]=items;
        }
        return;
    }
    ql2(i+1,w,v,items);
    vector<int>tmp=items;
    tmp.pb(i);
    ql2(i+1,w+a[i].w,v+a[i].v,tmp);
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
    ql(1,0,0,k,{});
    int p=o;
    o=0;
    ql2(k+1,0,0,{});
    sort(q+1,q+o+1);
    build(1,1,o);
    //for(int i=1;i<=o;i++) cout<<q[i].w<<" "<<q[i].v<<'\n'; cout<<'\n';
    for(int i=1;i<=o;i++){
        g[i]=q[i].w;
    }
    ii IT1,IT2;
    for(int i=1;i<=p;i++){
        int l=lower_bound(g+1,g+o+1,U-z[i].w)-g;
        int r=upper_bound(g+1,g+o+1,V-z[i].w)-g-1;
        ii val=get(1,1,o,l,r);
        if(val.w==-1) continue;
        if(maxx<z[i].v+val.w){
            maxx=z[i].v+val.w;
            IT1=z[i];
            IT2=ii(val.v,val.w);
        }
    }
    cout<<it1[IT1].size()+it2[IT2].size()<<'\n';
    for(int x:it1[IT1]) cout<<x<<" ";
    for(int x:it2[IT2]) cout<<x<<" ";
}

