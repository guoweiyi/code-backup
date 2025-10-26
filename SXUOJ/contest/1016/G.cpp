#include<bits/stdc++.h>
using namespace std;

int t,n,k;
string s;

void solve(){
    cin >> n >> k;
    cin >> s;

    int res = 0,last = -k;
    for(int i = 0;i < n;i++){
        if(s[i] == '1'){
           if(k <= i - last) res++,last = i;
            else last = i;
        }
    }
    cout << res << "\n";
}

int main(){
    cin >> t;
    while(t--) solve();
    return 0;
}