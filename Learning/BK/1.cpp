#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;
#define ll long long
vector<ll> arr;
// 递归算法

int f1(int n){
    int res;
    if(n == 1 || n == 2) res = 1;
    else res = f1(n - 1) + f1(n - 2);
    return res;
}
// 需要记忆化搜索 重复计算次数多
//递推-斐波那契

ll f2(ll n){
    arr.push_back(1);
    arr.push_back(1);
    for(int i = 2;i < n;i++){
        arr.push_back(arr[i - 1] + arr[i - 2]);
    }
    return arr[n - 1];
}
//猴子吃桃
ll f3(ll n){
    arr.push_back(1);
    for(int i = 1;i < n;i++){
        arr.push_back(( arr[i - 1]+ 1 )* 2);
    }
    return arr[n - 1];
}
//有规律式子的 n 项 递归递推结合

double f4(int n){
    arr.push_back(1);
    arr.push_back(1);
    for (int i = 2; i <= n; i++) {
        arr.push_back(arr[i - 1] + arr[i - 2]);
    }
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (double)arr[i] / arr[i + 1];
    }
    return sum;
}
//过河卒P1002 不考虑马
vector<vector<int>> mat(100, vector<int> (100, -1))
int f5(int x,int y){
    return f5(x - 1) + f(y - 1);
}
int main() {
    
    int n;
    cin >> n;
    cout << f4(n);
    return 0;
}
