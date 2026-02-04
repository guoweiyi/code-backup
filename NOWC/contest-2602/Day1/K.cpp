#include<iostream>
#include<vector>
#include<climits>
using namespace std;
using ll = long long;

int t;
vector<ll> res;

bool find(int n,ll sum,ll prod,ll last){
    if(res.size() == n - 1){
        if(prod <= 1) return false;

        if(sum % (prod - 1) == 0){
            ll x = sum / (prod - 1);
            if(x > last){
                res.push_back(x);
                return true;
            } 
        }
        return false;
    }
    for(ll i = last + 1;;i++){
        ll new_p = prod * i;
        ll new_s = sum + i;
        if(new_p > n + 500 && new_p > new_s + 500) break;
        res.push_back(i);
        if(find(n,new_s,new_p,i)) return true;
        res.pop_back();
    }
    return false;
}

void solve(){
    int n;cin >> n;
    if(n == 2){
        cout << "NO" << endl;return;
    }
    if(n == 1){
        cout << "YES" << endl << 1 << endl;return;
    }
    res.clear();
    if(find(n,0,1,0)){
        cout << "YES" << endl;
        for(int i = 0;i < n;i++){
            cout << res[i] << " ";
        }
        cout << endl;
    }
    else cout << "NO" << endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}