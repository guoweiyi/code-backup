#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
#define ll long long
void solve(){
    int n;cin >> n;
    vector<int> a(n);
    for(int i = 0;i < n;i++) cin >> a[i];
    if(n <= 2){
        cout << 0 << endl;
        return;
    }
    ll total = 0;
    for(int i = 0;i < n - 1;i++){
        total += abs(a[i] - a[i + 1]);
    }
    ll maxA = 0;
    maxA = max(maxA,(ll)abs(a[0] - a[1]));
    maxA = max(maxA,(ll)abs(a[n - 2] - a[n - 1]));
    for(int i = 1;i < n - 1;i++){
        ll olda = abs(a[i-1] - a[i]) + abs(a[i] - a[i+1]);
        ll newa = abs(a[i-1] - a[i + 1]);
        maxA = max(maxA,olda - newa);
    }
    cout << total - maxA << endl;
}

int main(){
    int t;cin >> t;
    while(t--){
        solve();
    }
    return 0;
}