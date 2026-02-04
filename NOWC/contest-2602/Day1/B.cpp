#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
int t;

void solve(){
    int n;cin >> n;
    vector<int> a,b;
    a.resize(n);b.resize(n);
    ll ans = 1;

    for(int i = 0;i < n;i++) cin >> a[i];
    for(int i = 0;i < n;i++) cin >> b[i];
    sort(a.begin(),a.end(),greater<int>());

    int x = 0,xb = 0;
    for(int i = 0;i < n;i++){
        while(xb < n && b[xb] >= a[i]) xb++;
        if(xb == n) break;
        x++;
    }
    for(int i = 1;i <= x;i++) ans = ans * i % 998244353;
    for(int i = 1;i <= n - x;i++) ans = ans * i % 998244353;
    cout << ans << endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}