#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n,ans = 0;
    cin >> n;
    vector<vector<int>> a(3, vector<int>(n));
    for(int i = 0;i < n;i++) cin >> a[0][i] >> a[1][i] >> a[2][i];
    for(int i = 0;i < n;i++){
        for(int j = i + 1;j < n;j++){
            if(abs(a[0][i] - a[0][j]) <= 5
                && abs(a[1][i] - a[1][j]) <= 5
                && abs(a[2][i] - a[2][j]) <= 5
                && abs(a[0][i] + a[1][i] + a[2][i] - a[0][j] - a[1][j] - a[2][j]) <= 10) ans++;
        }
    }
    cout << ans;
    return 0;
}