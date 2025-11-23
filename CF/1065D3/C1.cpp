#include<iostream>
#include<vector>
using namespace std;
#define ll long long

void solve(){
    int n;cin >> n;
    vector<ll> a(n+1),b(n+1);
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++) cin >> b[i];
    int Ta = 0,Tb = 0;
    for(int i = 1;i <= n;i++){
        Ta ^= a[i];
        Tb ^= b[i];
    }
    if(Ta == Tb){
        cout << "Tie" << endl;
    } 
    else{
        int lasti = -1;
        for(int i = 1;i <= n;i++) {
            if (a[i] != b[i]) lasti = i;
        }
        if(lasti == -1) cout << "Tie" << endl;
        else{
            if(lasti % 2 == 1) cout << "Ajisai" << endl;
            else cout << "Mai" << endl;
        }
    }
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int t;cin >> t;
    while(t--){
        solve();
    }
    return 0;
}