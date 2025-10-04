#include<bits/stdc++.h>
using namespace std;

bool cmp(pair<int, int> a,pair<int, int> b){
    //第二位从小到大
    if(a.second != b.second) return a.second < b.second;
    //第一位从大到小
    return a.first > b.first;
}
//如果传入cmp的两个元素相同 则他一定会返回false 与 sort 函数实现有关
// return a.first >= b.first 错误写法 会 RE
int main()
{
    vector<pair<int, int>> arr{{1, 9}, {2, 9}, {8, 1}, {0, 0}};
    sort(arr.begin(), arr.end(), cmp);//手写比较器
    // arr = [(0, 0), (8, 1), (2, 9), (1, 9)]
    for (auto ele : arr) cout << ele.first << " " << ele.second << endl;
    return 0;
}