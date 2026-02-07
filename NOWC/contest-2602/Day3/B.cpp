#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
int t;

ll gcd(ll a,ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

void solve(){
    int n;cin >> n;
    vector<ll> a(n);
    for(int i = 0;i < n;i++) cin >> a[i];

    for(int i = 0;i < n;i++) {
        for (int j = i + 1;j < n;j++) {
            if (gcd(a[i], a[j]) > 1) {
                cout << a[i] << " " << a[j] << endl;
                return;
            }
        }
    }
    cout << -1 << endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}