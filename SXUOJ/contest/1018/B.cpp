#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n,a,b,ans = 0;
#define rd read()
inline long long read()
{
    long long x = 0, y = 1;
    char c = getchar();
    while (c > '9' || c < '0')
    {
        if (c == '-')
            y = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        x = x * 10 + c - '0', c = getchar();
    return x * y;
}

int main() {
    ios::sync_with_stdio(false),cin.tie(nullptr);
    n = rd;
    a = rd;
    b = rd;
    vector<ll> arr(n); 
    for (int i = 0;i < n;i++) {
        cin >> arr[i];
    }
    ans += min(arr[0] * a * 1LL,b * 1LL);
    for (int i = 0;i < n - 1;i++) {
        ans += min(1LL * (arr[i + 1] - arr[i]) * a,b * 1LL);
    }
    cout << ans;
    return 0;
}
