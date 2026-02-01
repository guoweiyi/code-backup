#include<iostream>
#include<string>
using namespace std;
string str;
int main()
{
    int q;
    cin >> q;
    cin >> str;
    while(q--)
    {
        int opt,b,c;
        string a;
        cin >> opt;
        if(opt==1)
        {
            cin >> a;
            str+=a;
            cout << str << endl;
        }
        else if(opt==2)
        {
            cin >> b >> c;
            str=str.substr(b,c);
            cout << str << endl;
        }
        else if(opt==3)
        {
            cin >> b >> a;
            str.insert(b,a);
            cout << str <<endl;
        }
        else
        {
            cin >> a;
            //int pos= str.find(a);
            //cout <<(pos==string::npos ? -1 : pos)<< endl;
            cout << (int)str.find(a) << endl;
        }
    }
    return 0;
}