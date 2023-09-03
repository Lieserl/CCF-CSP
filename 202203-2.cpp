#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 2e5 + 100;
int n, m, k, t, c, q, a[maxn], sum[maxn];

int main()
{
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++)
    {
        cin >> t >> c;
        int temp = t - c + 1;
        a[temp > 0 ? temp : 1]++;
        a[t + 1]--;
    }

    for (int i = 1; i <= 200000; i++)
    {
        sum[i] = sum[i - 1] + a[i];
    }

    for (int i = 1; i <= m; i++)
    {
        cin >> q;
        cout << sum[q + k] << endl;
    }

    return 0;
}