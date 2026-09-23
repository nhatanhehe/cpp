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
const int N=1e5+5;
const int M=1e5+5;

struct Fenwick {
    vector<int> fen;

    Fenwick(int n=M) {
        fen.assign(n+1,0);
    }

    int query(int x) {
        if(x >= (int)fen.size()) {
            x=fen.size()-1;
        }

        if(x<0) {
            return 0;
        }

        int res=0;
        while(x) {
            res+=fen[x];
            x-=x&(-x);
        }

        return res;
    }

    void update(int x,int val) {
        while(x<(int)fen.size()) {
            fen[x]+=val;
            x+=x&(-x);
        }
    }
};

ll Check(vector<ii> points,int dist) {
    int first_good=0;
    Fenwick fen;
    ll res=0;

    for(int i=0;i<(int)points.size();i++) {
        while(points[i].fi-points[first_good].fi>dist) {
            fen.update(points[first_good].se,1);
            first_good++;
        }

        res+=i-first_good;
        res+=fen.query(points[i].se+dist);
        res-=fen.query(points[i].se-dist-1);
    }

    return res;
}

int Solve(vector<ii> points,ll k) {
    int res=0;

    sort(all(points));

    for(int p=20;p>=0;p--) {
        if(Check(points,res+(1<<p))<k) {
            res+=(1<<p);
        }
    }

    if(Check(points,0)>=k) {
        return 0;
    }

    return res+1;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll k;
    cin>>n>>k;

    vector<ii> points;

    for(int i=1;i<=n;i++) {
        int x,y;
        cin>>x>>y;

        points.pb({x,y});
    }

    cout<<Solve(points,k)<<'\n';

    return 0;
}