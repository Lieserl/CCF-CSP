#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 100;

int n, m;
int f[N][N];

int main()
{
    cin >> n >> m;

    f[0][1] = 1;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            f[i][j] = f[i - 1][j] + f[i][j - 1];

    cout << f[n][m] << endl;

    system("pause");

    return 0;
}
