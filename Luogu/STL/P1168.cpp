#include <bits/stdc++.h>
using namespace std;
#define ll long long

static inline ll read() {
    ll x = 0, s = 1;
    int c = getchar();
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    if (c == '-') { s = -1; c = getchar(); }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x * s;
}

int main() {
    ll n = read();
    ll A = read();
    ll B = read();
    vector<ll> a(n);
    for (ll i = 0; i < n; ++i) a[i] = read();
    ll ans = 0;
    ans += min(a[0] * A, B);
    for (ll i = 0; i + 1 < n; ++i) {
        ll d = a[i + 1] - a[i];
        ans += min(d * A, B);
    }
    printf("%lld\n", ans);
    return 0;
}
