#include<bits/stdc++.h>
using namespace std;

int L,sum = 0,ans = 0;

vector<int> finda(int n){//线性筛
    vector<bool> is_prime(n + 1,true);
    vector<int> primes;

    for(int i = 2;i <= n;i++){
        if(is_prime[i]) primes.push_back(i);

        for(int j = 0;j < primes.size() && i * primes[j] <= n;j++){
            is_prime[i * primes[j]] = 0;
            if(i % primes[j] == 0) break;
        }
    }
    return primes;
}

int main(){
    cin >> L;
    vector<int> pd = finda(L);
    vector<int> used;
    for(int ele : pd){
        if(sum + ele > L) break;
        sum += ele;
        cout << ele << endl;
        ans ++;
    }
    cout << ans << endl;
    return 0;
}