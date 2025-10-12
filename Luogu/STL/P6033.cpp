#include <iostream>   // cin, cout
#include <vector>     // std::vector
#include <queue>      // std::queue
#include <algorithm>  

using namespace std;

queue<long long> q1, q2;
long long ans = 0;
const int N = 100001;
vector<int> cnt(N, 0);
int maxA = 0;

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

long long getMin() {
	long long x;
    if (q1.empty()) {
        long long x = q2.front(); q2.pop();
        return x;
    }
    if (q2.empty()) {
        long long x = q1.front(); q1.pop();
        return x;
    }
    if (q1.front() < q2.front()) {
        long long x = q1.front(); q1.pop();
        return x;
    } else {
        long long x = q2.front(); q2.pop();
        return x;
    }
    return x;
}

int main() {
    long long n = rd;
    //桶排序
    for (int i = 0; i < n; i++) {
        int x = rd;
        cnt[x]++;
        if (x > maxA) maxA = x;  
    }
    for (int v = 1; v <= maxA; v++) while (cnt[v]--) q1.push(v);

    for (int i = 1; i < n; i++) {
        long long x = getMin();
        long long y = getMin();
        ans += x + y;
        q2.push(x + y);
    }

    cout << ans << "\n";
    return 0;
}