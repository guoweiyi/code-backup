//使用ele 拷贝的是副本 需要加上&确定内存地址

#include<iostream>
#include<string>
using namespace std;

string word,s;
int cnt = 0;

int main(){
    getline(cin,word);
    getline(cin,s);
    //bug 1 / 2
    for(auto &ele : word){
        if('A' <= ele && ele <= 'Z') ele += 'a' - 'A';
    }
    for(auto &ele : s){
        if('A' <= ele && ele <= 'Z') ele += 'a' - 'A';
    }
    word = ' ' + word + ' ';
    s = ' ' + s + ' ';
    if(s.find(word) == -1) cout << -1;
    else{
        int first = s.find(word);
        int nextpos = s.find(word);
        while(nextpos != -1){  
            cnt++;
            nextpos = s.find(word,nextpos + 1);
        }
        cout << cnt << " " << first;
    }
    return 0;
}