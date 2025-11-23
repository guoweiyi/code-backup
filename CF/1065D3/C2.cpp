#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n+1),b(n+1);
    for (int i = 1;i <= n;i++) cin >> a[i];
    for (int i = 1;i <= n;i++) cin >> b[i];

    int S = 0, T = 0;
    for (int i = 1; i <= n;i++) {
        S ^= a[i];
        T ^= b[i];
    }
    if (S == T){
        cout << "Tie\n"; 
        return;
    }
    int diff = S ^ T;//二进制上不同的位
    int p = 31 - __builtin_clz(diff); //统计前导零个数 bug1 新知识点 - 最高不同位
    // 谁控制 p 谁可获胜
    int last = -1;

    for(int i = 1; i <= n; i++) {
        if(((a[i]^b[i]) >> p) & 1) last = i;
    }
    if (last == -1) {
        if ( (S >> p) & 1 ) cout << "Ajisai\n";
        else cout << "Mai\n";
        return;
    }
    if(last & 1) cout << "Ajisai\n";
    else cout << "Mai\n";
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int t; cin >> t;
    while (t--){
        solve();
    }
    return 0;
}