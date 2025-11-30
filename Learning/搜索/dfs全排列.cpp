#include<vector>
#include<iostream>
using namespace std;
const int N = 10;
int n,path[N];//单次路径
bool st[N];//单次状态

void dfs(int e){
    if(e == n){
        for(int i = 0 ;i < n;i++) printf("%5d",path[i]);
        cout << endl;
        return;
    }
    for(int i = 1;i <= n;i++){
        if(!st[i]){
            st[i] = true;
            path[e] = i;
            dfs(e + 1);
            st[i] = false;
        }
    }
}
int main(){
    cin >> n;
    dfs(0);
    return 0;
}