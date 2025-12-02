//无需在安全到达点中找最低值 直接判断 如果该点从未被炸过那就是安全点
//只要 BFS 搜到一个永远不会被炸的格子，那就是安全点，返回并结束程序

#include<vector>
#include<queue>
#include<iostream>
using namespace std;
using PII = pair<int,int>;
const int INFA = 1e9;

int m,maxx,maxy;
vector<vector<int>> t,d;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

void init(int x,int y,int time){
    t[x][y] = min(t[x][y],time);
    
    for(int i = 0;i < 4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx >= 0 && ny >= 0) t[nx][ny] = min(t[nx][ny], time);
        //bug1 忘加 xy bug5记得加越界判断
    }
}

void bfs(){
    queue<PII> arr;
    arr.push({0,0});
    d[0][0] = 0;
    while(!arr.empty()){
        auto p = arr.front();
        arr.pop();

        if(t[p.first][p.second] == INFA){
            cout << d[p.first][p.second];
            return;
        }

        for(int i = 0;i < 4;i++){
            int nx = p.first + dx[i];
            int ny = p.second + dy[i];
            int arrive = d[p.first][p.second] + 1;//bug2 先计算
            if(nx >= 0 && nx <= maxx && ny >= 0 && ny <= maxy && d[nx][ny] == -1 && arrive < t[nx][ny]){
                d[nx][ny] = arrive;
                arr.push({nx,ny});
            }
        }
    }
    cout << -1;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> m;
    t.resize(500,vector<int>(500,INFA));//bug3被炸时间最大
    d.resize(500,vector<int>(500,-1));
    for(int i = 0;i < m;i++){
        int x,y,time;cin >> x >> y >> time;
        //bug4不能写 x-- (0,0)已经是题目标点
        maxx = max(maxx,x + 2);
        maxy = max(maxy,y + 2);
        init(x,y,time);
    }
    bfs();
    return 0;
}