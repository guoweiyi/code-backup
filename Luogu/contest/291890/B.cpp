#include<iostream>
using namespace std;
#define ll long long

void solve(){
    ll x1, x2, x3;
    ll y1, y2, y3;
    cin >> x1 >> x2 >> x3;
    cin >> y1 >> y2 >> y3;

    if (x1 * y1 + x2 * y2 + x3 * y3 == 0) cout << "Orthogonal";
    else cout << "Non-Orthogonal";
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    solve();
    return 0;
}
