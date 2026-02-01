#include<iostream>
#include<vector>
using namespace std;

int n,m;
vector<vector<bool>> arr;
vector<vector<int>> ans;

int main(){
    cin >> n >> m;
    arr.resize(n,vector<bool>(m));
    ans.resize(n,vector<int>(m));
    for(int i = 0;i < n;i++){
        string s;cin >> s;
        for(int j = 0;j < m;j++){
            if(s[j] == '*') arr[i][j] = 1;
            else arr[i][j] = 0;
        }
    }
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            int cnt = 0;
            if(arr[i][j]){
                ans[i][j] = -1;
                continue;
            } 
            for(int dx = -1; dx <= 1; dx++){
                for(int dy = -1; dy <= 1; dy++){
                    if(dx == 0 && dy == 0) continue;
                    int x = i + dx, y = j + dy;
                    if(x >= 0 && x < n && y >= 0 && y < m){
                        if(arr[x][y]) cnt++;
                    }
                }
            }
            ans[i][j] = cnt;
        }
    }
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(ans[i][j] == -1) cout << "*";
            else cout << ans[i][j];
        }
        cout << "\n";
    }
    return 0;
}