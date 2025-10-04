#include<bits/stdc++.h>
using namespace std;

int main(){
    map<int, int> mp;

    mp[2] = 1;
    mp[0] = 3;
    mp[999] = 666;
    // mp.erase(2);mp.size();mp.empty();

    for(map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it){
        cout << it->first << " " << it->second << endl;
    }
    for (auto &ele : mp) cout << ele.first << " " << ele.second << endl;
    

    cout << mp.count(2) << endl;//出现次数 但普通 map 有互异性 只能返回 1/0

    if (mp.find(2) != mp.end()) cout << "Yes" << endl; //返回的不是尾迭代器 故找到了

    cout << mp[2] << endl;



    map<string, int> mp2;
    vector<string> word;
    word.push_back("waw");
    word.push_back("waw");
    word.push_back("w1w");
    word.push_back("waw");
    for (int i = 0; i < word.size(); i++) mp2[word[i]]++;
    for (auto &ele : mp2) cout << ele.first << " " << ele.second << endl;
    return 0;
}