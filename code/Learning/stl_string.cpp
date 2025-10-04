#include<bits/stdc++.h>
using namespace std;
int main(){
    string s1 = "123123123"; 
    s1[0] = 'b';
    string s2(3,'1');
    cout << s1 + s2 << endl;
    cout << s1.substr(3,4) << endl; // 子串
    //第二个参数不是子串终点！不是子串终点
    //不要用 scanf printf
    if(s1.find("312") != string::npos) cout << "yes" << endl; // 找到返回第一个位置


    string a1 = "123123123",a2 = "123.123123"; 
    int a3 = 6662;
    long long x1 = stold(a1);//互转
    long double x2 = stold(a2);
    string s = to_string(a3);
    return 0;
}