#include<iostream>
#include<math.h>
using namespace std;

long long a,t = 0,x = 0;

int main(){
    while(cin>>a) x+=a,t++;
    cout << x * (long long)pow(2,t-1);
    return 0;
}