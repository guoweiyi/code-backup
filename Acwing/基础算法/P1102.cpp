#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std; 

vector<int> a;
int n,c;
ll ans = 0;

int main(){
    cin >> n >> c;
    a.resize(n);
    for(int i = 0;i < n;i++) cin >> a[i];
    sort(a.begin(), a.end());

    int i = 0, j = 1;

    while (i < n && j < n) {
        ll diff = a[j] - a[i];

        if (diff < c) {
            j++;
        } 
        else if (diff > c) {
            i++;
            if (i == j) j++;
        } 
        else {
            ll v1 = a[i], v2 = a[j];
            ll cnt1 = 0, cnt2 = 0;

            //i 的重复
            while (i < n && a[i] == v1) cnt1++,i++;
            //j 的重复
            while (j < n && a[j] == v2) cnt2++,j++;
            
            ans += cnt1 * cnt2;

            if (i == j) j++;
        }
    }

    cout << ans;
    return 0;
}
