#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
int t;

void solve(){
    int n,j = 0,o = 0;cin >> n;
    vector<int> a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        if(a[i] % 2 == 0 && a[i] % 2 != i % 2) o++;
        else if(a[i] % 2 != 0 && a[i] % 2 != i % 2) j++;
    } 
    if(j == o) cout << j << endl;
    else cout << -1 << endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}