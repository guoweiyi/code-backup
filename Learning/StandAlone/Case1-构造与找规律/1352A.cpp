#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
int t;

void solve(){
    int n,cnt = 1,c = 0;cin >> n;
    vector<int> dt(5);
    while(n > 0){
        int d = n % 10;
        dt[cnt] = d;
        n /= 10;
        cnt ++;
        if(d != 0) c++;
    }
    cout << c << endl;
    while(cnt--){
        if(dt[cnt] == 0) continue;
        cout << dt[cnt];
        for(int i = 1;i < cnt;i++) cout << 0;
        cout << " "; 
    }
    cout << endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}