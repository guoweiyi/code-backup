#include<iostream>
#include<vector>
#include<climits>
using namespace std;
using ll = long long;

int n;
ll m,maxa = -1;
vector<ll> a;

ll check(int w){
    ll ans = 0;
    for(int i = 0;i < n;i++){
        if(a[i] - w > 0) ans += a[i] - w;
    }
    return ans;
}

int main(){
    cin >> n >> m;
    a.resize(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        maxa = max(maxa,a[i]);
    }
    int l = 0,r = maxa;
    while(l < r){
        int mid = (l + r + 1) >> 1;
        if(check(mid) >= m) l = mid;
        else r = mid - 1;
    }
    cout << r;
    return 0;
}