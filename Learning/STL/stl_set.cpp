#include<bits/stdc++.h>
using namespace std;

int main(){
    set<int> st;
    st.insert(1);
    st.insert(2);
    st.insert(2);//互异性 不会存入


   for (auto it = st.begin(); it != st.end(); it++) cout << *it << endl;



   // for (auto ele : st) cout << ele << endl;
    //for (auto &ele : st) cout << ele << endl;


//  st.erase(2);

  //  if(st.find(1) != st.end()) cout << "yes" << endl;
    //找到1返回指向1的迭代器 找不到返回尾迭代器

  //  cout << st.count(2) << endl; // 返回这个元素有几个 代替上方功能 只有1/0
    //st.clear;
    //st.size(); st.empty();判空
    
    
    return 0;
}