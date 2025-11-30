#include<queue>
#include<iostream>
#include<vector>
using namespace std;
typedef pair<int,int> PII;

int n,m;
vector<vector<int>> g,d;//g存图d存每一点到七点多距离

int bfs(){
    queue<PII> arr;

    d[0][0] = 0;
    arr.push({0,0});
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,1,0,-1};
    
    while(arr.size()){
        auto t = arr.front();
        arr.pop();
        
        for(int i = 0;i < 4;i++){
            int x = t.first + dx[i];
            int y = t.second + dy[i];
            if(x >= 0 && x < n && y >= 0 && y < m && g[x][y] == 0 && d[x][y] == -1){
                d[x][y] = d[t.first][t.second] + 1;
                arr.push({x,y});
            }
        }
    }
    return d[n - 1][m - 1];
}

int main(){
    cin >> n >> m;
    g.resize(n,vector<int>(m));
    d.resize(n,vector<int>(m,-1)); //bug1

    for(int i = 0;i < n;i++)
        for(int j = 0;j < m;j++)
            cin >> g[i][j];
    cout << bfs() << endl;
    return 0;
}