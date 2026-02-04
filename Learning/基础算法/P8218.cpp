#include<iostream>
#include<vector>
using namespace std;

vector<int> a,b;

int main(){
    int n,m;cin >>n;
    a.resize(n + 5);
    b.resize(n + 5);

    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++) b[i] = b[i - 1] + a[i];

    cin >> m;

    while(m--){
        int l,r;cin >> l >> r;
        cout << b[r] - b[l - 1] << endl;
    }
    return 0;
}