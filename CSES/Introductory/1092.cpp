#include<bits/stdc++.h>
using namespace std;
int a[1000006],b[1000006],c[1000006];
int main(){
    long long t=0,k=0,l,d=0;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        t+=i;
    }
    if(t%2!=0) cout<<"NO";
    else{
        cout<<"YES"<<'\n';
    l=t/2;
        for(int i=n;i>=1;i--){
                k++;
                b[k]=i;
                l=l-i;
                if(l<i){
                    if(l>0){
                    k++;
                    b[k]=l;
                    }
                    break;
                }
        }
    cout<<k<<'\n';
    for(int i=1;i<=k;i++){
        cout<<b[i]<<" ";
    }
    for(int i=1;i<=n;i++){
        c[b[i]]++;
    }
    cout<<'\n';
    for(int i=1;i<=n;i++){
        if(c[i]==0) d++;
    }
    cout<<d<<'\n';
    for(int i=1;i<=n;i++){
        if(c[i]==0) cout<<i<<' ';
    }
    }
    // cout<<k<<'\n';
    // for(int i=1;i<=k;i++){
    //     c[b[k]]++;
    //     cout<<b[k]<<" ";
    // }
    // cout<<'\n';
    // for(int i=1;i<=n;i++){
    //     if(c[i]==0) d++;
    // }
    // cout<<d<<'\n';
    // for(int i=1;i<=n;i++){
    //     if(c[i]==0) cout<<i<<" ";
    // }
}

