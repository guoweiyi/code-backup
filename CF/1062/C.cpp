#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

int t;
vector<int> arr;
void solve(){
    int n;  
    bool has_even = false, has_odd = false;
    cin >> n;
    arr.resize(n);
    for(int i = 0;i < n;i++) cin >> arr[i];

    for (auto ele : arr) {
        if (ele % 2 == 0) has_even = true;
        else has_odd = true;
    }

    if (has_even && has_odd) {
        sort(arr.begin(), arr.end());
    }

    for (int ele : arr) cout << ele << " ";
    cout << endl;
}
int main() {
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
