#include<vector>
#include<iostream>
#include<queue>
using namespace std;
using PII = pair<int,int>;
vector<vector<int>> d;
int n,m,x,y;

void bfs(){
    queue<PII> arr;
    arr.push({x,y});
    int dx[8] = {2,-2,2,-2,-1,1,-1,1};
    int dy[8] = {1,1,-1,-1,2,2,-2,-2};

    while(arr.size()){
        auto t = arr.front();
        arr.pop();
        
        for(int i = 0;i < 8;i++){
            int nx = t.first + dx[i];
            int ny = t.second + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(d[nx][ny] == -1){
                d[nx][ny] = d[t.first][t.second] + 1;
                arr.push({nx,ny});
            }
        }
    }
}
int main(){
    cin >> n >> m >> x >> y;
    d.resize(n,vector<int>(m,-1));
    x--,y--;
    d[x][y] = 0;
    bfs();
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++) cout << d[i][j] << " ";
        cout << endl;
    }
    return 0;
}