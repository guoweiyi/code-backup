#include<iostream>
#include<vector>
#include<climits>
using namespace std;
using ll = long long;
int t;

void solve(){
    int a,b,c;cin >> a >> b >> c;
    int mina = min(a,b);
    mina = min(mina,c);
    a -= mina + 1;
    b -= mina + 1;
    c -= mina + 1;
    if(a == b && b == c) cout << "YES\n";
    else if ((a == b || b == c || a == c) && (abs(b - a) < 2 && abs(b - c) < 2 && abs(a - c) < 2)) cout << "YES\n";
    else cout << "NO\n";
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}