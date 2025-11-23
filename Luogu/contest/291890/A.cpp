#include<iostream>
using namespace std;
#define ll long long

void solve(){
    ll n,m,r,c;
    ll x1,y1,x2,y2;
    cin >> n >> m >> r >> c;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << (x2 / r - x1 /r + 1) * (y2 / c - y1 /c + 1);
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    solve();
    return 0;
}