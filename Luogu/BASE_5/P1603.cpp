#include<bits/stdc++.h>
using namespace std;

priority_queue<int,vector<int>,greater<int>> arr;
int ans = 0;

void js(int a){
    a = pow(a,2);
    a %= 100;
    arr.push(a);
    ans++;
}

void finda(string s){
    if(s == "one") js(1);
    else if(s == "two") js(2);
    else if(s == "three") js(3);
    else if(s == "four") js(4);
    else if(s == "five") js(5);
    else if(s == "six") js(6);
    else if(s == "seven") js(7);
    else if(s == "eight") js(8);
    else if(s == "nine") js(9);
    else if(s == "ten") js(10); 
    else if(s == "eleven") js(11);  
    else if(s == "twelve") js(12);  
    else if(s == "thirteen") js(13);  
    else if(s == "fourteen") js(14);   
    else if(s == "fifteen") js(15);  
    else if(s == "sixteen") js(16);  
    else if(s == "seventeen") js(17);  
    else if(s == "eighteen") js(18);  
    else if(s == "nineteen") js(19);  
    else if(s == "twenty") js(20); 

    else if(s == "a") js(1); 
    else if(s == "both") js(2); 
    else if(s == "another") js(1); 
    else if(s == "first") js(1); 
    else if(s == "second") js(2); 
    else if(s == "third") js(3);  
}

int main(){
    while(1){
        string s;
        cin >> s;
        finda(s);
        if(s == ".") break;
    }
    if(arr.size() == 0) cout << 0;
    for(int i = 1;i <= ans;i++){
        if(arr.top() == 0) continue;
        if(i == 1 ) cout << arr.top();
        else if(i != 1 && arr.top() < 10) cout << 0 << arr.top();
        else cout << arr.top();
        arr.pop();
    }
    return 0;

}