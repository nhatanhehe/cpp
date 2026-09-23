#include<bits/stdc++.h>
#define int long long
#define ii pair<int,int>
#define fi first
#define se second
#define task ""
using namespace std;

const int N = 1e6 + 5, mod = 1e9 + 7;
const int oo = 1e18;
int n, a[N];
deque<int> dq;
stack<int> st;
main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if(fopen(task ".inp", "r")){
        freopen(task ".inp", "r", stdin);
        freopen(task ".out", "w", stdout);
    }
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = n; i >= 1; i--) st.push(a[i]);

    string s;
    cin >> s;

    for(char c : s)
    {
        if(c == 'C')
        {

            if(st.size()) dq.push_front(st.top());
            else cerr<<"Ko du S";
            st.pop();
        }
        else
        {

            if(dq.size()) st.push(dq.back());
            else cerr<<"Ko du H";dq.pop_back();
        }
    }
    while(st.size())
    {
        cout << st.top() << ' ';
        st.pop();
    }
}
