//二维vector的resize使用

#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> arr;
vector<vector<int>> temp;
void st(int n){
    int cnt = 1;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            arr[i][j] = cnt++;
        }
    }
}

void re(int x,int y,int r,bool z){
    if (z == 0)
    {
        for(int i = x - r;i <= x + r;i++){
            for(int j = y - r;j <= y + r;j++){
                temp[x - y + j][x + y - i] = arr[i][j];
            }
        }      
        for(int i = x - r;i <= x + r;i++){
            for(int j = y - r;j <= y + r;j++){
                arr[i][j] = temp[i][j];
            }
        }
    }
    else{
        for(int i = x - r;i <= x + r;i++){
            for(int j = y - r;j <= y + r;j++){
                temp[x + y - j][y - x + i] = arr[i][j];
            }
        }      
        for(int i = x - r;i <= x + r;i++){
            for(int j = y - r;j <= y + r;j++){
                arr[i][j] = temp[i][j];
            }
        }
    }
}

int main(){
    int n,x,y,r,m;
    bool z;
    cin >> n >> m;
    arr.resize(n+1, vector<int>(n+1));
    temp.resize(n+1, vector<int>(n+1));
    st(n);
    while(m--){
        cin >> x >> y >> r >> z;
        re(x,y,r,z);
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}