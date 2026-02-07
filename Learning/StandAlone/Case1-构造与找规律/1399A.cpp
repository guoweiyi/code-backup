#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
int t;

void solve(){
    int n;cin >> n;
    bool ok = true;
    vector<int> a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    for(int i = 0;i < n;i++){
        if(i != 0)
            if(a[i] - a[i - 1] > 1) ok = false;
    }
    if(ok == 1) cout << "YES" << endl;
    else cout << "NO" << endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}