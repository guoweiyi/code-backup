#include<iostream>
#include<vector>
#include<climits>
using namespace std;
using ll = long long;
int t;

void solve(){
    int n; cin >> n;
    if(n == 1){
        cout << "YES\n1\n";
    }
    else if(n == 3){
        cout << "YES" << endl << "1 2 3" << endl;
    }
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