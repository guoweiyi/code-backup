#include<bits/stdc++.h>
using namespace std;

int n;
int a[101] = {0};
int ans[101] = {0};//答案数组

void cheng(int x){//高精乘法
    int j = 0;//进位
    for(int i = 100;i >= 0;i--){
        a[i] = a[i] * x + j;
        j = a[i] / 10;
        a[i] %= 10;
    }
}
void qh(){//高精加法
    int j = 0;
    for(int i = 100;i >= 0;i--){
        ans[i] += a[i] + j;
        j = ans[i] / 10;
        ans[i] %= 10; 
    }
}

void sc(){
    int j = 0;
    for(int i = 0;i <= 100;i++){//找到答案
        if(ans[i] != 0){
            j = i;
            break;
        }
    }
    for(int i = j;i <= 100;i++) cout << ans[i];
}

int main(){
    cin >> n;
    ans[100] = a[100] = 1;//初始
    for(int i = 2;i <= n;i++){
        cheng(i);
        qh();
    }
    sc();
    return 0;
}