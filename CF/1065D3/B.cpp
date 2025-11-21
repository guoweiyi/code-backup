#include<iostream>
#include<vector>
using namespace std;
#define ll long long

void solve(){
    int n;cin >>n;
    vector<ll> arr(n);
    for(int i = 0;i < n;i++) cin >> arr[i];    
    vector<ll> ans = arr;
    if(arr[0] == -1 && arr[n - 1] == -1) ans[0] = 0,ans[n - 1] = 0;
    else if(arr[0] == -1) ans[0] = ans[n - 1];
    else if(arr[n - 1] == -1) ans[n - 1] = ans[0];

    for(int i = 0;i < n;i++){
        if(ans[i] == -1) ans[i] = 0;
    }
    cout << llabs(ans[n - 1] - ans[0]) << endl;
    for(int i = 0;i < n;i++) cout << ans[i] << (i == n - 1 ? '\n' : ' ');
}

int main(){
    int t;cin >> t;
    while(t--){
        solve();
    }
    return 0;
}