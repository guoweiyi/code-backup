#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
void solve(){
    int n;cin >> n;
    vector<int> a(n);
    int minA = 1e5;
    for(int i = 0;i < n;i++){
        cin >> a[i];
        minA = min(minA,a[i]);
    }
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    int ans = 0;
    for(int i = minA;i >= 0;i--){
        auto e = upper_bound(a.begin(),a.end(),i);
        if(e == a.end()) continue;
        if(*e <= 2 * i) continue;
        ans = max(ans,*e - i);
    }
    cout << ans << endl;
}

int main(){
    int t;cin >> t;
    while(t--){
        solve();
    }
    return 0;
}