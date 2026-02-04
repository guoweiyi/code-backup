#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> a,s;

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);

    int n,m,q;cin >> n >> m >> q;
    a.resize(n + 1, vector<int>(m + 1));
    s.resize(n + 1, vector<int>(m + 1));
    s[0][0] = 0;

    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            cin >> a[i][j];

    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];

    while(q--){
        int x1,y1,x2,y2;cin >> x1 >> y1 >> x2 >> y2;
        cout << s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1] << endl;
    }
    return 0;
}