#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        int target = 1001; 
        cout << n << '\n';
        for (int i = 1; i <= n; ++i) {
            cout << i << ' ' << (target - i) << '\n';
        }
    }
    return 0;
}