#include<bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr{0,1,2,3,4,5,6,7}; //使用二分要求数列有序
    int pos = lower_bound(arr.begin(), arr.end(),8) - arr.begin();
    int pos2 = upper_bound(arr.begin() + 2, arr.end(),999) - arr.begin();
    if (pos2 == arr.size()) cout << "no" << endl;//找不到
//    cout << pos2 << endl;

    reverse(arr.begin() + 2,arr.begin() + 6);//反转 为左闭右开区间 [2,6) 反转 2345
    for (auto ele : arr) cout << ele << endl;

    cout << max({1,3,4,5,62,24,5,6,1,0}) << endl; 
    //去重
    vector<int> arr1{1,2,1,4,5,4,4};
    //1 1 2 4 4 4 5
    //1 2 4 5 *(unique返回*的位置)
    sort(arr1.begin(),arr1.end());
    arr1.erase(unique(arr1.begin(),arr1.end()), arr1.end());
    for (auto ele : arr1) cout << ele << endl;

    return 0;
}