#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<unordered_map>
using namespace std;
using PII = pair<int,int>;

vector<vector<int>> g,d;
// g存图 负数表示传送口 1 表示草地 0 表示玉米 d存答案时间
// 终点为 100
int n,m,startx,starty;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
unordered_map<int, vector<pair<int,int>>> tp;

PII getAnother(int x,int y,int id){
    if(tp[id][0].first == x && tp[id][0].second == y) return tp[id][1];
    else return tp[id][0];
}


void bfs(){
    d[startx][starty] = 0;
    queue<PII> arr;
    arr.push({startx,starty});

    while(!arr.empty()){
        auto e = arr.front();
        arr.pop();

        for(int i = 0;i < 4;i++){
            int nx = dx[i] + e.first;
            int ny = dy[i] + e.second;
            int arrive = d[e.first][e.second] + 1;
            if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;

            if(g[nx][ny] == 999){
                cout << arrive;
                return;
            }
            else if(g[nx][ny] < 0){
                auto nxt = getAnother(nx,ny,g[nx][ny]);
                
                if (d[nxt.first][nxt.second] == -1 || arrive < d[nxt.first][nxt.second]){
                    d[nxt.first][nxt.second] = arrive;
                    arr.push(nxt);
                }
            }
            else if(g[nx][ny] == 1 && d[nx][ny] == -1){
                d[nx][ny] = arrive;
                arr.push({nx,ny});
            }
        }
    }
}


int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> n >> m;
    g.resize(n,vector<int>(m));
    d.resize(n,vector<int>(m,-1));

    for(int i = 0;i < n;i++){
        string s;cin >> s;
        for(int j = 0;j < m;j++){
            if(s[j] == '#') g[i][j] = 0;
            else if(s[j] == '.') g[i][j] = 1;
            else if(s[j] == '@') g[i][j] = 1,startx = i,starty = j;
            else if(s[j] == '=') g[i][j] = 999;
            else{
                int id = -(s[j] - 'A' + 1);
                g[i][j] = id;
                tp[id].push_back({i, j});
            }
        }
    }
    bfs();
    return 0;
}