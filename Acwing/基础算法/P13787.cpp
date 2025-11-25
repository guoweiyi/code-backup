#include<iostream>
#include<vector>
#define ll long long
using namespace std;

vector<vector<int>> b;

void insert(int x1,int y1,int x2,int y2){
    b[x1][y1] += 1;
    b[x2 + 1][y1] -=1;
    b[x1][y2 + 1] -=1;
    b[x2 + 1][y2 + 1] +=1;
}
int main(){
    int n,m;cin >> n >> m;
    ll ans = 0;

    b.resize(n + 5,vector<int>(n + 5));

    while(m--){
        int x1,y1,x2,y2;cin >> x1 >> y1 >> x2 >> y2;
        insert(x1,y1,x2,y2);
    }

    for(int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++){
            b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
            ans += (i+j) ^ b[i][j];
        }
    cout << ans;
    return 0;
}