#include<iostream>
#include<map>
#include<algorithm>
using namespace std;
using ll = long long;
int t;

void solve(){
    int n;cin >> n;
    map<int,int> count;
    for(int i = 0;i < n;i++){
        int a;cin >> a;
        count[a]++;
    } 
    int c1 = count.size();
    int c2 = 0;
    for(auto e : count) c2 = max(c2, e.second);
    if(c1 == c2) cout << c2 - 1 << endl;
    else cout << min(c1,c2) << endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}