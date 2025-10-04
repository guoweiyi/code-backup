#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,ans = 1;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        ans = 2 * (ans + 1);
    }
    cout << ans ;
    return 0;
}