#include<iostream>
using namespace std;

const int N =1010;
int n, m, q, a[N][N], b[N][N];

void insert(int x1, int y1, int x2, int y2, int c)
{
    b[x1][y1] += c; //整个矩阵
    b[x2 + 1][y1] -= c; // x2之后(长x2+1...右端，宽y1的长方形)
    b[x1][y2+ 1] -= c; //y2之后 (长x1..右端, 宽y2 + 1..的长方形)
    b[x2 + 1][y2 + 1] += c; // 右下角小矩阵，从x2+1, y2+ 1往右下的矩形
}

int main()
{
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            insert(i, j, i, j, a[i][j]); //同理，根据上述矩阵分析，a[i][j]+c <=> b(i,j) 的那些操作。如果矩阵塌缩为点，即在b(i,j)插入了a(i,j)的值
            // 想象a(i,j) + c的运算a(i,j)设为0，c=(a(i,j))即通过insert函数b(i,j)表达了0到a(i,j)的信息转换。这次insert后b(i,j)的前缀和=a(i,j)

    while(q--)
    {
        int x1, y1, x2, y2, c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        insert(x1, y1, x2, y2, c);
    }

    for(int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1]; //bij前缀和定义 = aij; 
            // 即x方向(横着看)+ (i-1,j)和之前的,
            // y方向(竖着看)+ (i, j - 1)和之上的。由于多加了一倍重合的(i-1, j-1)往前往上的部分，所以减回来。总运算即为(2D二维前缀和)
            //对于矩阵坐标不熟的可以背一下
    for (int i = 1;i <= n; i++){
        for (int j = 1; j <= m; j++)
            printf("%d ", b[i][j]); //以上操作过后b(i,j)变成了前缀和,即为a(i,j)
        cout << endl;
    }
    return 0;
}