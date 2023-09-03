#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e5 + 10;
int n, k, ans = 1e9 + 10, a[maxn], sum[maxn];

bool judge(int x)
{
    int summ = 0, cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        summ += a[i];
        if (summ >= x)
            summ = 0, cnt++;
    }

    return cnt > n / 2;
}

int main()
{
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    if (k == !(n % 2))
    {
        for (int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + a[i];
        for (int i = 1; i <= n / 2; i++)
        {
            int temp = sum[i + n / 2] - sum[i - 1];
            ans = min(ans, temp);
        }
    }
    else
    {
        int l = 1, r = 1e9 + 10;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (judge(mid))
                l = mid + 1;
            else
                r = mid - 1;
        }
        ans = l - 1;
    }

    cout << ans << endl;

    return 0;
}