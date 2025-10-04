#include <bits/stdc++.h>
using namespace std; 
int main()
{

int k;
double sn=0;
scanf ("%d", &k);
for(int i=1;;++i){
        sn += 1.0 / i;
        if (sn > k){
            printf ("%d\n", i);
            break;
        }
}
return 0;
}