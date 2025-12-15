#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>> g;
int m,n;
int dx[4] = {0,-1,0,1};
int dy[4] = {1,0,-1,0};
bool yes_all = false;
int main(){
    cin >> m >> n;
    g.resize(m,vector<int>(n));
    for(int i = 0;i < m;i++){
        for(int j = 0;j < n;j++){
            cin >> g[i][j];
        }
    }
    for(int i = 0;i < m;i++){
        for(int j = 0;j < n;j++){
            int ok = 0;
            for(int k = 0;k < 4;k++){
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                if(g[i][j] > g[nx][ny]) ok++;
            }
            if(ok == 4){
                yes_all = true;
                cout << g[i][j] << " " << i + 1 << " " << j + 1 << endl;
            } 
        }
    }
    if(!yes_all) cout << "None" << " " << m << " " << n << endl;
    return 0;
}
