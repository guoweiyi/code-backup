#include <bits/stdc++.h>
using namespace std;

long long ans = 0;
int n;

int main() {
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end()); 
    for (int i = 0; i < n; i += 2) {
        long long sum = a[i] + a[i + 1];
        if (sum > 0) ans += sum; 
    }
    cout << ans;
    return 0;
}
