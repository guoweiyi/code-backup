#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
int t;

void solve(){
    int n,m;cin >> n >> m;
    ll suma = 0,sumb = 0;
    vector<int> a(n),b(m);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        suma += a[i];
    }
    for(int i = 0;i < m;i++){
        cin >> b[i];
        sumb += b[i];
    }
    if(suma == sumb) cout << 1 << endl;
    else{
        ll D = llabs(suma - sumb);
        vector<int> heavy;
        if(suma > sumb) heavy = a;
        else heavy = b;

        sort(heavy.begin(), heavy.end(), greater<ll>());
        ll sum_tmp = 0;int cnt = 0;
        for (ll x : heavy) {
            sum_tmp += x;
            cnt++;
            if (sum_tmp >= D) break;
        }
        cout << cnt << '\n';
    }
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}