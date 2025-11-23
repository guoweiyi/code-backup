#include<iostream>
using namespace std;
#define ll long long

void solve(){
    int n;cin >> n;
    int pre,cur;
    ll ans = 0;
    cin >> pre;
    for (int i = 0;i < n - 1;i++) {
        cin >> cur;
        if ((pre & 1) != (cur & 1)) ans++;
        pre = cur;
    }
    cout << ans;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    solve();
    return 0;
}
