/*
第一次 53 少考虑了多个起点
第二次 AC
5
0 0 0 0 0
1 1 1 1 1
1 0 0 0 1
1 1 1 1 1
0 0 0 0 0
*/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
using PII = pair<int,int>;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
vector<vector<int>> a,visted;
int n,startx,starty;

void bfs(){
    queue<PII> arr;
    arr.push({startx,starty});
    visted[startx][starty] = 1;
    
    while(!arr.empty()){
        auto e = arr.front();
        arr.pop();
        for(int i = 0;i < 4;i++){
            int nx = e.first + dx[i];
            int ny = e.second + dy[i];
            if(nx < 0 || nx >=n || ny < 0 || ny >= n || a[nx][ny] == 1) continue;
            if(visted[nx][ny] == -1){
                arr.push({nx,ny});
                visted[nx][ny] = 1;
            }
        }
    } 
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin >> n;
    
    a.resize(n,vector<int>(n));
    visted.resize(n,vector<int>(n,-1));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cin >> a[i][j];
        }
    }
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(i == 0 || j == 0 || i == n - 1 || j == n - 1){
                if(visted[i][j] == -1 && a[i][j] == 0 ){
                    startx = i,starty = j;
                    bfs();
                }
            }
        }
    }
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(a[i][j] == 1) cout << 1 <<" ";
            if(a[i][j] == 0){
                if(visted[i][j] == -1) cout << 2 << " ";
                else cout << 0 << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}