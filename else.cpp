#include<bits/stdc++.h>
using namespace std;
// Cho mot so n, xac dinh xem la n la chan hay le.
main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a,b,c,x,y,z;
    cin>>a>>b>>c>>x>>y>>z;
    if(z>c){
        cout<<1;
    }
    else{
        if(z<c) cout<<2;
        if(z==c){
            if(y>b) cout<<1;
            else{
                if(y<b) cout<<2;
                if(y==b){
                    if(x>a) cout<<1;
                    else cout<<2;
                }
            }
        }
    }
}
