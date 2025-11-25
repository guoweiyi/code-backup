#include<iostream>
#include<vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 0;i < n;i++) cin >> a[i];
    while(q--){
        int x;cin >> x;
        int l = 0,r = n - 1;
        while(l < r){
            int mid = (l + r) >> 1;
            if(a[mid] >= x) r = mid;
            else l = mid + 1;
        }
        if(a[l] != x) cout << "-1 -1" << endl;
        else{
            cout << l << " ";
            l = 0,r = n - 1;
            while(l < r){
                int mid = (l + r + 1) >> 1;
                if(a[mid] <= x) l = mid;
                else r = mid - 1;
            }
            cout << l << endl;
        }
    }
    return 0;
}