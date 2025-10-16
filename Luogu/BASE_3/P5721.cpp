#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin >> n;
    int ans = 0;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= (n - i + 1);j++){
            ans++;
            if(ans < 10) cout << 0 << ans;
            else cout << ans;
        }
        cout << endl;
    }
    return 0;
}