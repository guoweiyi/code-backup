//八皇后 dfs 复现
#include<iostream>
#include<vector>
using namespace std;

const int N = 15;

int n,count = 0;
bool ans[N][N];
bool col[N],dg[N * 2],udg[N * 2];

void dfs(int e){
    if(e == n){
        if(count < 3){
            for(int i = 0;i < n;i++){
                for(int j = 0;j < n;j++){
                    if(ans[i][j]){
                        cout << j + 1 << " ";//bug4要加一
                        break;
                    }
                }
            }
            cout << endl;
        }
        count++;
        return;
    }
    //e为行i为列
    for(int i = 0;i < n;i++){
        if(!col[i] && !dg[i + e] && !udg[i - e + n]){//bug1/2udg计算逻辑 n 为保证不越界
            ans[e][i] = col[i] = dg[i + e] = udg[i - e + n] = true;
            //bug3上方e行i列 写反
            dfs(e + 1);
            ans[e][i] = col[i] = dg[i + e] = udg[i - e + n] = false;
        }
    }
}

int main(){
    cin >> n;
    dfs(0);
    cout << count;
    return 0;
}