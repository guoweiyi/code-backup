/*
马可以这样走
先横走 2，再竖走 1：
变化	dx	dy
(→→↑)	+2	+1
(→→↓)	+2	-1
(←←↑)	-2	+1
(←←↓)	-2	-1

先竖走 2，再横走 1：
变化	dx	dy
(↑↑→)	+1	+2
(↑↑←)	-1	+2
(↓↓→)	+1	-2
(↓↓←)	-1	-2

*/
#include<queue>
#include<iostream>
#include<vector>
using namespace std;
typedef pair<int,int> PII;

int n,m,x,y;
vector<vector<int>> g,d;//g存图d存每一点到起点的距离

void bfs(){
    queue<PII> arr;

    arr.push({x,y});
    int dx[8] ={2,-2,2,-2,-1,1,-1,1};
    int dy[8] = {1,1,-1,-1,2,2,-2,-2};
    
    while(arr.size()){
        auto t = arr.front();
        arr.pop();
        
        for(int i = 0;i < 8;i++){
            int nx = t.first + dx[i];
            int ny = t.second + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m && g[nx][ny] == 0 && d[nx][ny] == -1){
                d[nx][ny] = d[t.first][t.second] + 1;
                arr.push({nx,ny});
            }
        }
    }
}

int main(){
    cin >> n >> m >> x >> y;
    g.resize(n + 1,vector<int>(m + 1,0));
    d.resize(n + 1,vector<int>(m + 1,-1));
    x--,y--;
    d[x][y] = 0;
    bfs();
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++)
            cout << d[i][j] << " ";
        cout << endl;
    }
    return 0;
}