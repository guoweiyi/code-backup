#include<bits/stdc++.h>
using namespace std;

stack<int> arr;
string s;
int num = 0;

int main(){
    getline(cin, s, '@');
    
    for( char ch : s){
        if(ch == '.'){
            arr.push(num);
            num = 0;
        }
        else if(ch == '+'){
            int a = arr.top(); arr.pop();
            int b = arr.top(); arr.pop();
            arr.push(a+b);
        }
        else if(ch == '-'){
            int a = arr.top(); arr.pop();
            int b = arr.top(); arr.pop();
            arr.push(b-a);
        }
        else if(ch == '*'){
            int a = arr.top(); arr.pop();
            int b = arr.top(); arr.pop();
            arr.push(a*b);
        }
        else if(ch == '/'){
            int a = arr.top(); arr.pop();
            int b = arr.top(); arr.pop();
            arr.push(b/a);
        }
        else num = num * 10 + (ch - '0');
    }
    cout << arr.top();
    return 0;
}