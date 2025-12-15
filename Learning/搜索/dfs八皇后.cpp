#include<iostream>
#include<vector>
using namespace std;
const int N = 20;
int n;
char g[N][N];
bool col[N],dg[N],udg[N];//列 对角线 反对角线

void dfs(int e){
    if(n == e){
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){ 
                cout << g[i][j];
            }
            cout << endl; 
        }
        cout << endl;
        return;
    }
    // e代表当前行，i代表当前列 循环可放置的列
    for(int i = 0;i < n;i++){
        if(!col[i] && !dg[i + e] && !udg[i - e + n]){
            // 正对角线：r + c 的值相等
            // 反对角线：r - c 的值相等，需要加上 n 消除负数
            g[e][i] = 'Q';
            col[i] = dg[i + e] = udg[i - e + n] = true;
            dfs(e + 1);// 递归到下一行
            col[i] = dg[i + e] = udg[i - e + n] = false;
            g[e][i] = '.';
        }
    }
}

int main(){
    cin >> n;
    for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++)
            g[i][j] = '.';
    dfs(0);
    return 0;
}