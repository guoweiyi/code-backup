#include<iostream>
#include<vector>
using namespace std;
void solve(){
    int n;cin >> n;
    vector<int> p = {0};
    for(int i = 1;i <= n;i++){
        vector<int> next;
        next.reserve(1 << i);
        for(auto e : p) next.push_back(e * 2 + 1);
        for(int j = 0;j < p.size();j++) next.push_back(j * 2); 
        p = next;
    }
    for(auto e : p) cout << e << " ";
    cout << endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int t;cin >> t;
    while(t--){
        solve();
    }
    return 0;
}