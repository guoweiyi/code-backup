//四个科目分开讨论搜索

#include<iostream>
#include<vector>
using namespace std;

vector<int> s;
vector<int> n(4);
int maxdeep,nowtime,maxtime,sum,ans = 0;

void dfs(int e){
    if(e == maxdeep){
        maxtime = max(maxtime,nowtime);
        return;
    }
    if(nowtime + s[e] <= sum / 2){
        nowtime += s[e];
        dfs(e + 1);
        nowtime -= s[e];
    }
    dfs(e + 1);
}

int main(){
    for(int i = 0;i < 4;i++) cin >> n[i];
    for(int i = 0;i < 4;i++){
        s.resize(n[i],0);
        sum = 0;
        for(int j = 0;j < n[i];j++){//bug1 重复使用 i
            cin >> s[j];
            sum += s[j];
        }
        maxdeep = n[i];
        maxtime = nowtime = 0;
        dfs(0);
        ans += (sum - maxtime);
    }
    cout << ans;
    return 0;
}