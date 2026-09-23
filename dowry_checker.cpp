#include "testlib.h"
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ii pair<int,int>
#define iii pair<int,ii>
#define all(x) x.begin(),x.end()
#define fi first
#define se second
using namespace std;
int a[200005];
ii items[35];
main(int argc, char *argv[])
{
    registerTestlibCmd(argc, argv);
    int n=inf.readLong(),u=inf.readLong(),v=inf.readLong();
    for(int i=1; i<=n; i++)
    {
        items[i].fi=inf.readLong();
        items[i].se=inf.readLong();
    }
    ll mxsum=0;
    int m=ans.readLong();
    for(int i=1; i<=m; i++)
    {
        int idx=ans.readLong();
        mxsum+=items[idx].se;
    }
    int q=ouf.readLong();
    ll outsum=0,outsumw=0;
    for(int i=1; i<=q; i++)
    {
        int idx=ouf.readLong();
        outsum+=items[idx].se;
        outsumw+=items[idx].fi;
    }
    if(q==0&&m==0) quitf(_ok,"gioi lam con trai cua ta");
    if(outsum==mxsum&&outsumw>=u&&outsumw<=v) quitf(_ok,"gioi lam con trai cua ta");
    else quitf(_wa,"ga` lam con trai cua ta");
}
