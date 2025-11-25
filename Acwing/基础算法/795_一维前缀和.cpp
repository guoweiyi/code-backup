#include<iostream>
#include<vector>
using namespace std;
vector<int> a,b;

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;
    cin >> n >> q;
    a.resize(n+1);
    b.resize(n+1);
    b[0] = 0;
    for(int i = 1;i <= n;i++) cin >> a[i];

    for(int i = 1;i <= n;i++) b[i] = b[i - 1] + a[i];

    while(q--){
        int l,r;cin >> l >> r;
        cout << b[r] - b[l - 1] << endl;
    }
    return 0;
}