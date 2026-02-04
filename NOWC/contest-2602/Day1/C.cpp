#include<iostream>
#include<vector>
#include<climits>
using namespace std;
using ll = long long;
int t;

void solve(){
    int n;
    ll sum = 0;
    cin >> n;
    vector<ll> a;
    a.resize(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        sum += a[i];
    }
    ll ans = sum;
    if(n <= 2){
        cout << sum << endl;
        return;
    }
    ans = max(ans,a[0] + a[n - 1] + (ll)(n - 2) * max(a[0],a[n - 1]));
    for(int i = 1;i < n - 1;i++){
        ll l = i - 1;
        ll r = n - 2 - i;//i+1 -> n-2
        ll a1 = a[0] + a[n - 1] + a[i] + l * max(a[0],a[i]) + r * max(a[i],a[n - 1]);
        ans = max(a1,ans);
    }
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