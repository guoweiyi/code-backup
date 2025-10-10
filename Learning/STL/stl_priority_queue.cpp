#include<bits/stdc++.h>
using namespace std;

int main(){
    //大顶堆
    priority_queue<int> pque1;
 //   pque.pop(); //弹出最大元素

    //小顶堆
    priority_queue<int, vector<int>,greater<int>> pque;
    pque.push(4);
    cout << pque.top() << endl;
     pque.push(3);
    cout << pque.top() << endl;
     pque.push(2);
    cout << pque.top() << endl;
     pque.push(1);
    cout << pque.top() << endl;



    return 0;
}