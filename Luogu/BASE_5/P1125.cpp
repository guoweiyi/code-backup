//单个计数
//质数判断

#include<bits/stdc++.h>
using namespace std;

int cnt[256],maxn = 0,minn = INT_MAX;
string s;

bool isPrime(int n) {
    if (n <= 1) return false;      // 0,1 和负数都不是质数
    if (n <= 3) return true;       // 2,3 是质数
    if (n % 2 == 0 || n % 3 == 0) return false; // 剔除 2 和 3 的倍数
    for (int i = 5; 1LL * i * i <= n; i += 6) { // 6k±1 检测
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

bool isPrimeLL(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i <= n / i; i += 6) { // 用 n / i 防止 i*i 溢出
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main(){
    cin >> s;
    for(int i = 0;i < s.size();i++){
        cnt[(unsigned char)s[i]]++;
    }
    for(int i = 0;i < 256;i++){
            if(maxn < cnt[i]) maxn = cnt[i];
            if(minn > cnt[i] && cnt[i] != 0) minn = cnt[i];
    }
    if(isPrimeLL(maxn - minn)) cout << "Lucky Word" << endl << maxn - minn;
    else cout << "No Answer" << endl << 0;
    return 0;
}