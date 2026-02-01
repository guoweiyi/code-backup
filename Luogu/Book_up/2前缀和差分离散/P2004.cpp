#include<iostream>
#include<vector>
#include<climits>
using namespace std;

vector<vector<int>> a,s;
int n,m,c,k,p,ans = INT_MIN,x,y;

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> n >> m >> c;
    a.resize(n + 1,vector<int>(m + 1));
    s.resize(n + 1,vector<int>(m + 1));

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin >> a[i][j];
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            s[i][j] = a[i][j] - s[i - 1][j - 1] + s[i][j - 1] + s[i - 1][j];
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(i + c - 1 > n) continue;
            else k = i + c - 1;
            if(j + c - 1 > m) continue;
            else p = j + c - 1;
            int ans_tmp = s[k][p] + s[i - 1][j - 1] - s[k][j - 1] - s[i - 1][p];
            if(ans_tmp > ans){
                ans = ans_tmp;
                x = i,y = j;
            }
        }
    }
    cout << x << " " << y;
    return 0;
}