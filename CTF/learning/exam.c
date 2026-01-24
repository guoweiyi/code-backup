#include <stdio.h>
int main()
{   
    int n = 6,m = 9,r,t;
    if(n < m) t = n,n = m,m = t;
    r = n % m;
    while(r!=0){
        n = m;
        m = r;
        r = n % m;
    }
    printf("%d",m);
	return 0;
}