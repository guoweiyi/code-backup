#include<vector>
#include<queue>
#include<iostream>
using namespace std;

vector<vector<int>> g,d;
int n,m,t,sx,sy,fx,fy,ans = 0;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
void dfs(int x,int y){
    if(x == fx && y == fy){
        ans++;
        return;
    }
    g[x][y] = 1;
    for(int i = 0;i < 4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if(g[nx][ny] == 0) dfs(nx,ny);
    }
    g[x][y] = 0;//bug1
}



int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> n >> m >> t;
    cin >> sx >> sy >> fx >> fy;
    sx--,sy--,fy--,fx--;
    g.resize(n,vector<int>(m,0));
    d.resize(n,vector<int>(m,-1));
    while(t--){
        int x,y;cin >> x >> y;
        x--,y--;
        g[x][y] = 1;
    }
    dfs(sx,sy);
    cout << ans;
    return 0;
}