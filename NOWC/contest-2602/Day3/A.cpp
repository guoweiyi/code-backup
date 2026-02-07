#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void solve(){
    int x;cin >> x;
    bool ok = false;
    for(int k = 1; k * (k + 1) <= x;k++) {
        if (k * (k + 1) == x) {
            ok = true;
            break;
        }
    }
    if (ok) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    solve();
    return 0;
}