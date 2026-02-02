#include<iostream>
#include<vector>
using namespace std;
int n,m;
vector<int> a;

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> n >> m;
    a.resize(n);
    for(int i = 0;i < n;i++) cin >> a[i];
    while(m--){
        int x;
        cin >> x;
        int l = 0,r = n - 1;
        while(l < r){
            int mid = (l + r) >> 1;
            if(x <= a[mid]) r = mid;
            else l = mid + 1;
        }
        if(a[r] != x) cout << -1 << " ";
        else cout << r + 1 << " ";
    }
    return 0;
}