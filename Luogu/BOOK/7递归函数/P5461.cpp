// bug ^ n 不是 2 的 n 次方，而是按位异或 2 ^ (n - 1) 要写成：1 << (n - 1)
#include<iostream>
#include<vector>
using namespace std;

vector<vector<bool>> arr;

void fx(int x,int y,int n){
    if(n == 0) arr[x][y] = 1;
    else{
        fx(x,y + (1 << (n - 1)),n - 1);
        fx(x + (1 << (n - 1)),y,n - 1);
        fx(x + (1 << (n - 1)),y + (1 << (n - 1)),n - 1);//bug
    }
}

int main(){
    int n;cin >> n;
    arr.resize(1 << n, vector<bool>(1 << n, 0));

    fx(0,0,n);

    for (auto row : arr) {
        for (auto x : row) {
            cout << x << " ";
        }
        cout << "\n";
    }
    return 0;
}