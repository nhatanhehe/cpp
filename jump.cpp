#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef long double ld;
#define pb push_back
#define pf push_front
#define debug(x) cout<< #x << " = "<< x <<'\n'
#define Task "JUMP"
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

ll n,d,h[N];
vector<ll>v;
ll st[4*N];

ll getpos(ll x){
    return lower_bound(all(v),x)-v.begin()+1;
}

ll query(ll id,ll l,ll r,ll u,ll v){
    if(v<l||r<u) return 0;
    if(u<=l&&r<=v) return st[id];
    ll mid=(l+r)/2;
    return max(query(id*2,l,mid,u,v),query(id*2+1,mid+1,r,u,v));
}

void update(ll id,ll l,ll r,ll pos,ll val){
    if(l==r){
        st[id]=max(st[id],val);
        return;
    }
    ll mid=(l+r)/2;
    if(pos<=mid) update(id*2,l,mid,pos,val);
    else update(id*2+1,mid+1,r,pos,val);
    st[id]=max(st[id*2],st[id*2+1]);
}

main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    if(fopen(Task ".inp","r")){
        freopen(Task ".inp","r",stdin);
        freopen(Task ".out","w",stdout);
    }

    cin>>n>>d;
    for(int i=1;i<=n;i++){
        cin>>h[i];
        v.pb(h[i]);
    }

    sort(all(v));
    v.erase(unique(all(v)),v.end());

    ll sz=v.size();
    ll ans=0;

    for(int i=1;i<=n;i++){
        ll best=0;

        ll pos1=upper_bound(all(v),h[i]-d)-v.begin();
        if(pos1>0)
            best=max(best,query(1,1,sz,1,pos1));

        ll pos2=lower_bound(all(v),h[i]+d)-v.begin()+1;
        if(pos2<=sz)
            best=max(best,query(1,1,sz,pos2,sz));

        ll dp=best+1;
        ans=max(ans,dp);

        ll pos=getpos(h[i]);
        update(1,1,sz,pos,dp);
    }

    cout<<ans;
}