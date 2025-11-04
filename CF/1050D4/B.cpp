#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

int t;

void solve(){
    int n, m, l, r;
    cin >> n >> m >> l >> r;
    if(m <= r) cout << 0 <<' '<< m <<endl;
    else{
        int x=m-r;
        cout << -x << ' ' << r <<endl;
    }
}
int main() {
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
