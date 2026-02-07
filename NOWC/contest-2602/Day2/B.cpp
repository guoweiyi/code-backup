#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
int t;

void solve(){
    int n,ans = 0,maxa = -1;
    int max_c = 0;
    cin >> n;
    vector<int> a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        if(a[i] > maxa){
            ans = i;
            maxa = a[i];
        }
    }
    for(int i = 0;i < n;i++){
        if(a[i] == maxa){
            max_c++;
        }
    }
    if(max_c % 2 != 0){
        for(auto e : a){
            if(e == maxa) cout << 1;
            else cout << 0;
        }
    }
    else{
        for(auto e : a){
            if(e < maxa) cout << 1;
            else cout << 0;
        }
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