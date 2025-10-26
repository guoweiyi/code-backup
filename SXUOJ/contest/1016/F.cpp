#include<bits/stdc++.h>
using namespace std;

int n,t;

void solve() {
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
   	long long sum = 0;
    for (auto ele : a) {
         sum += ele;
    }
    cout << sum - n + 1  << endl;
}

int main() {
    cin >> t;
    while (t--) solve();
    return 0;
}
