#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, a, b;
    if (!(cin >> n >> a >> b)) return 0;
    cout << max(0LL, a + b - n) << '\n';
    return 0;
}