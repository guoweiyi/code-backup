#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
int t;
vector<ll> a;

void solve(){
    int n;
    ll k;
    cin >> n >> k;
    a.clear();a.resize(n);
    for(int i = 0;i < n;i++) cin >> a[i];
    ll maxa = a[0] + k;
    for(int i = 0;i < n - 1;i++){
        maxa = max(maxa,a[i] + a[i + 1]);
    }
    maxa = max(maxa,k + a[0]);
    maxa = max(maxa,k + a[n - 1]);
    cout << maxa << endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}