#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve(){
    ll a, b, c;
    cin >> a >> b >> c;
    if((a + b + c) % 3 == 0) {
        ll x = (a + b + c) / 3;

        if(a > x || b > x) cout << "NO\n";
        else cout << "YES\n";
    } 
    else cout << "NO\n";
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
