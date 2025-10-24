#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll s, t;
    cin >> n >> s >> t;
    vector<ll> a(n + 1);
    vector<ll> pre(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }
    ll tot = pre[n];

    for (int d = 0; d <= 60; ++d) {
        // sub * 2^d > s && (tot - sub) * 2^d > t
        // sub > s / 2^d && sub < tot - t / 2^d
        long double pow2 = powl(2.0L, d); 
        long double low1 = (long double)s / pow2;
        long double high1 = (long double)tot - (long double)t / pow2;

        long double low2 = (long double)t / pow2;
        long double high2 = (long double)tot - (long double)s / pow2;

        bool ok = false;

        for (int l = 1; l <= n; ++l) {
            for (int r = l; r <= n; ++r) {
                ll sub = pre[r] - pre[l - 1];

                // 攻南守北
                if (sub > low1 && (tot - sub) > (long double)t / pow2) {
                    ok = true;
                    break;
                }

                // 攻北守南
                if (sub > low2 && (tot - sub) > (long double)s / pow2) {
                    ok = true;
                    break;
                }
            }
            if (ok) break;
        }
        if (ok) {
            cout << d << "\n";
            return 0;
        }
    }
    cout << -1 << "\n";
    return 0;
}
