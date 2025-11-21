#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;
#define ll long long
const ll N = 1000010;
int t;
vector<ll> a;

ll gcd2(ll a,ll b){
    while(b != 0){
        ll t = a % b;
        a = b;
        b = t;
    }
}

void solve(){
    int n;  
    cin >> n;
    a.resize(n);
    for(int i = 0;i < n;i++) cin >> a[i];
    ll g = a[0];
    for(int i = 0;i < n;i++) g = gcd2(g,a[i]);
    for(ll i = 2;i <= N;i++){
        if(gcd2(g,i) == 1){
            cout << i << endl;
            return;
        }
    }
    cout << endl;
}
int main() {
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
