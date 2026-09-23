#include<bits/stdc++.h>
using namespace std;
bool M1;
#define PI 3.14159265358979323846
#define sz(a) (int)a.size()
#define all(x) x.begin(),x.end()
#define ii pair<int,int>
#define iii pair<int,ii>
#define iv pair<ii,ii>
#define se second
#define fi first
#define ffi fi.fi
#define sfi se.fi
#define sse se.se
#define fse fi.se
#define lt(i, c, d) for(int i = c; i <= d; ++i)
#define fl(i, c, d) for(int i = d; i >= c; --i)
#define pb push_back
#define emb emplace_back
#define emf emplace_front
#define em emplace
#define look_memory cerr<<abs(&M2-&M1)/1024.0/1024<<'\n'
#define look_time   cerr << "TIME : " << clock() * 0.001 << "s" <<'\n'
const int N=2e3+5,lg=30,mod=1e9+7;
mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int u,int v){
 return u+rd()%(v-u+1);
}
int dx[]={1,0,-1,0,1,1,-1,-1};
int dy[]={0,-1,0,1,1,-1,1,-1};
int node,a[N],dem[N],soluong,ans;
string s[N];
void giai(int lef,int rig){

    int r=lef;
//    cout <<lef<<" "<<rig<<":\n";
    for(int l=lef;l<=rig;++l){
        while(r<=rig&&dem[a[r]]>1){
            dem[a[r]]--;
            ++r;
        }
        if(r>l)dem[a[l]]++;
        ans=min(ans,rig-lef+1-r+l);
//        cout <<l<<" "<<r<<'\n';
        r=max(r,l+1);
    }
//    cout <<'\n';

}
bool M2;
void solve(){
    cin >> node;
    vector<string>nen;
    for(int i=1;i<=node;++i){
        cin >> s[i];
        nen.emb(s[i]);
    }
    sort(all(nen));
    nen.erase(unique(all(nen)),nen.end());
    for(int i=1;i<=node;++i){
        for(int j=0;j<sz(nen);++j){
            if(s[i]==nen[j]){
                a[i]=j;
                break;
            }
        }
//        cout << a[i]<<'\n';
    }
    ans=node;
    int l=1,n=sz(nen);
    for(int r=1;r<=node;++r){
        dem[a[r]]++;
        if(dem[a[r]]==1)++soluong;
        while(l<=r&&soluong==n&&dem[a[l]]>1){
            dem[a[l]]--;
            ++l;
        }
//        cout <<l<<" "<<r<<" "<<soluong<<" "<<n<<'\n';
        if(soluong==n)
        giai(l,r);
    }
    cout << ans;
}
main()
{
  srand(time(0));
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    #define task "streetfood"
    if(fopen(task".inp","r")){
      freopen(task".inp","r",stdin);
      freopen(task".out","w",stdout);
    }
    int t=1;
 //   cin >> t;
while(t--){
    solve();
//    cout<<'\n';
}
look_memory;
look_time;
}
