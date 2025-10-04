#include<bits/stdc++.h>
using namespace std;

int main(){
    stack<double> stk;
    stk.push(1.0);
    stk.push(1.4);
    stk.pop();
    cout << stk.top() << endl;//栈顶
//  错误写法 stl 栈无清空  stk.clear();
    cout << stk.size() << endl;
    cout << stk.empty() << endl;
//  不可访问内部元素
    return 0;
}