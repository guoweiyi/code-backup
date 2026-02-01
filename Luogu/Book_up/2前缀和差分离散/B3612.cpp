#include<iostream>
#include<vector>
using namespace std;

vector<int> a,b;
int n,m;

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> n;
    a.resize(n+1);
    b.resize(n+1);
    for(int i = 1;i <= n;i++) cin >> a[i];
    cin >> m;
    b[0] = 0;
    for(int i = 1;i <= n;i++) b[i] = b[i - 1] + a[i];
    while(m--){
        int l,r;
        cin >> l >> r;
        cout << b[r] - b[--l] << endl;
    }
    return 0;
}