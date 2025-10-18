#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m, k, s;
    cin >> n >> m >> k >> s;

    long long minA = s, maxA = s;

    for (int i = 0; i < m; ++i) {
        long long t, h;
        int change = 0;//记录变化量

        cin >> t >> h;
 //       if (h >= k) continue;
        if (t == 0) {
            change = max(1LL, s - h);
        } else {    
            change = min(n, s + h);
        }

        if(abs(change - s) >= k) continue;
        s = change;
        maxA = max(maxA, s);
        minA = min(minA, s);
    }
    cout << minA << " " << maxA << "\n";
    return 0;
}
