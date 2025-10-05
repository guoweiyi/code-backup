#include<bits/stdc++.h>
using namespace std;

priority_queue<long long, vector<long long>, greater<long long>> arr;
long long n,ans = 0;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> n)) return 0;
    for(int i = 1;i <= n;i++){
        long long tmp;
        cin >> tmp;
        arr.push(tmp);
    }
    while(arr.size() > 1){
        long long x = arr.top(); arr.pop();
        long long y = arr.top(); arr.pop();
        long long z = x + y;
        arr.push(z);
        ans += z;
    }
    cout << ans;
    return 0;
}