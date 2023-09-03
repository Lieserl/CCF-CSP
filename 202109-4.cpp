#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 20;
double ans = 0, p[maxn], dp[1 << maxn][84];
int cnt[1 << maxn];
int n, k;

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    for (int i = 1; i < (1 << n); i++)
    {
        int x = i;
        while (x)
        {
            cnt[i]++;
            x &= x - 1;
        }
    }

    for (int i = 1; i <= n; i++)
        dp[1 << (i - 1)][1] = p[i];

    for (int i = 1; i < (1 << n); i++)
    {
        for (int j = 1; j <= 1 + (n - 1) * k; j++)
        {
            if (cnt[i] + (j - cnt[i]) / k == n)
            {
                ans += dp[i][j] * j;
                continue;
            }

            for (int w = 1; w <= n; w++)
            {
                if (i & (1 << (w - 1)))
                    dp[i][j + 1] += dp[i][j] * p[w];
                else
                    dp[i + (1 << (w - 1))][j + 1] += dp[i][j] * p[w];
            }
        }
    }

    printf("%.10lf", ans);

    system("pause");

    return 0;
}