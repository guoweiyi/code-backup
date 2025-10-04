#include<bits/stdc++.h>
using namespace std;

int main(){
    //尾接
    vector<int> arr;
    arr.push_back(3);
    arr.push_back(2);
    arr.push_back(31);

  //  cout << arr.size() << endl;

  // arr.pop_back();

  //  arr.resize(5,3); //改长赋初值 改短直接删
    sort(arr.begin(), arr.end(), greater<int>());// 从大到小
    for (auto ele : arr) cout << ele << endl;

//  cout << arr.empty() << endl;
    
 // arr.clear();
    return 0;
}