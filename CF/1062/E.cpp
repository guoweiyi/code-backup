#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n, k, x;
vector<ll> a;

// 检查是否存在至少 k 个点，距离所有朋友 ≥ D
bool check(ll mid, vector<ll>& a,ll k,ll s) {
   
}

void solve() {
    cin >> n >> k >> x;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    
}

int main() {
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
