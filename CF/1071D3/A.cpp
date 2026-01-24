#include<iostream>
using namespace std;

void solve(){
    int k,x;cin >> k >> x;
    cout << x * k + 1 << endl;
}

int main(){
    int t;cin >> t;
    while(t--){
        solve();
    }
    return 0;
}