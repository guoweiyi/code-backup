#include<bits/stdc++.h>
using namespace std;

int l,m;

int main(){
    cin >> l >> m;
    vector<bool> arr(l + 1,false);
    for(int a = 0;a < m;a++){
        int i,j;
        cin >> i >> j;
        for(int b = i;b <= j;b++) arr[b] = true;
    }
    int ans = 0;
    for(int i = 0;i <= l;i++){
        if(!arr[i]) ans++;
    }
    cout << ans;
    return 0;
}