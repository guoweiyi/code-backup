#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> a,b;
int n,ans = -10000000;

int qsum(int x1,int y1,int x2,int y2){
    return b[x2][y2] - b[x1 - 1][y2] - b[x2][y1 - 1] + b[x1 - 1][y1 - 1];
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> n;
    a.resize(n + 1,vector<int>(n + 1));
    b.resize(n + 1,vector<int>(n + 1));
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++) cin >> a[i][j];
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++){
            b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + a[i][j];
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = i; k <= n; k++)
                for (int l = j; l <= n; l++)
                    ans = max(ans, (qsum(i, j, k, l)));
    cout << ans;
    return 0;
}