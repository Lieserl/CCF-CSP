#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int maxn = 1e5 + 10;
const int mod = 929;
int w, s, k, a[maxn], code[maxn], d[maxn], g[maxn];
string str;

int check(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return 0;
    if (ch >= 'a' && ch <= 'z')
        return 1;
    if (ch >= '0' && ch <= '9')
        return 2;

    return -1;
}

int main()
{
    cin >> w >> s >> str;

    if (s == -1)
        k = 0;
    else
        k = pow(2, s + 1);

    int pre = 0;
    int indexx = 0;

    for (auto &i : str)
    {
        int now = check(i);
        if (now == 0)
        {
            if (pre == 0)
                a[indexx++] = i - 'A';
            else if (pre == 1)
                a[indexx++] = 28, a[indexx++] = 28, a[indexx++] = i - 'A';
            else
                a[indexx++] = 28, a[indexx++] = i - 'A';
        }
        else if (now == 1)
        {
            if (pre == 0)
                a[indexx++] = 27, a[indexx++] = i - 'a';
            else if (pre == 1)
                a[indexx++] = i - 'a';
            else
                a[indexx++] = 27, a[indexx++] = i - 'a';
        }
        else
        {
            if (pre == 0)
                a[indexx++] = 28, a[indexx++] = i - '0';
            else if (pre == 1)
                a[indexx++] = 28, a[indexx++] = i - '0';
            else
                a[indexx++] = i - '0';
        }

        pre = now;
    }

    if (indexx % 2)
        a[indexx++] = 29;

    int ind = 0;
    for (int i = 0; i < indexx; i = i + 2)
        code[ind++] = a[i] * 30 + a[i + 1];

    int num = ind + k + 1;
    while (num % w)
        code[ind++] = 900, num++;

    int base = -3;
    // 运算时记得随时取模 只要计算k遍
    g[0] = 1;
    for (int i = 1; i <= k; i++, base = base * 3 % mod)
        for (int j = i - 1; j >= 0; j--)
            g[j + 1] = (g[j + 1] + base * g[j]) % mod;

    // + 1 !!!!!!!!!!!!!!  总长度ind + 1
    d[0] = ind + 1;
    for (int i = 1; i <= ind; i++)
        d[i] = code[i - 1];

    for (int i = 0; i <= ind; i++)
    {
        int x = d[i];
        d[i] = 0;
        // i j 都能搞反你啥子嘛
        for (int j = 1; j <= k; j++)
            // 别眼瞎了
            d[i + j] = (d[i + j] - x * g[j]) % mod;
    }

    cout << ind + 1 << endl;

    for (int i = 0; i < ind; i++)
        cout << code[i] << endl;

    for (int i = ind + 1; i <= ind + k; i++)
        cout << (-d[i] % mod + mod) % mod << endl;

    system("pause");

    return 0;
}