#include<iostream>
using namespace std;

void solve(){
    int n;cin >>n;
    if(n % 2 == 1) cout << 0;
    else cout << n / 4 + 1;
    cout << endl;
}

int main(){
    int t;cin >> t;
    while(t--){
        solve();
    }
    return 0;
}