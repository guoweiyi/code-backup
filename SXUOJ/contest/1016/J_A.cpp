#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n,ans = 0;
ll m, k;

void solve(){
    cin >> n >> m >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            ll dist = a[j] - a[i];
            ll back = min(abs(k - a[i]), abs(k - a[j]));
            ll total = dist + back;
            if (total <= m)
                ans = max(ans, j - i + 1);
        }
    }
    cout << ans;
}
int main() {
    solve();
    return 0;
}
