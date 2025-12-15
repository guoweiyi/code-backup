#include<iostream>
#include<vector>
using namespace std;
vector<int> a;
int n,k,ans = 0;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true; 
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; 1LL * i * i <= n; i += 6) { // 6k±1 检测
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

void dfs(int idx,int cnt,int sum){
    if(cnt == k){
        if(isPrime(sum)) ans++;
        return;
    }
    if(idx == n) return;
    dfs(idx + 1,cnt + 1,sum + a[idx]);
    dfs(idx + 1,cnt,sum);
}

int main(){
    cin >> n >> k;
    a.resize(n);
    for(int i = 0;i < n;i++) cin >> a[i];
    dfs(0,0,0);
    cout << ans;
    return 0;
}