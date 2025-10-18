#include <bits/stdc++.h>
using namespace std;

int n, m;
long long sum = 0;
int cnt = 0;

int main() {
    cin >> n >> m;

    vector<int> a(n), b(m), c(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    for (int i = 0; i < m; i++) cin >> c[i];

    int maxA = *max_element(a.begin(), a.end());

    for (int i = 0; i < m; i++) {
        if (maxA >= b[i]) {
            sum += c[i];
            cnt++;
        }
    }

    cout << sum / cnt << "\n";
    return 0;
}
