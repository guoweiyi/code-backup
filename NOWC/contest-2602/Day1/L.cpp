#include<iostream>
using namespace std;

int n,x;

int main(){
    cin >> n;
    switch(n % 10)
    {
        case 0: cout << 1;break;
        case 1: case 7: case 3: case 9: cout << 10;break;
        case 2: case 4: case 8: case 6: cout << 5;break;
        case 5: cout << 2;
    }
    return 0;
}