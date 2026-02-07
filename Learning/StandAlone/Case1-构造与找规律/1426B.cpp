#include<iostream>
#include<map>
#include<algorithm>
using namespace std;
using ll = long long;
int t;

void solve(){
    int n,x,ans;cin >> n >> x;
    bool ok = 0;
    for(int i = 1;i <= n;i++) {
        int x1,x2,y1,y2;cin >> x1 >> x2 >> y1 >> y2;
        if(x2 == y1) ok = 1;
    }
    if((x & 1) || !ok) {//奇数
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}