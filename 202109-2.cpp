#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 5e5 + 10;
int n, ans, cnt = 0, id[maxn], a[maxn];

int main()
{
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i], id[i] = i;

    sort(id + 1, id + n + 1, [](const auto &i, const auto &j) -> bool
         { return a[i] < a[j]; });

    for (int i = 1; i <= n + 1; i++)
    {
        if (a[i] == 0 && a[i - 1] != 0)
            cnt++;
    }

    int x = 0, ans = cnt;

    for (int i = 1; i <= n; i++)
    {
        if (a[id[i]])
        {
            int u = id[i];
            if (a[u] && a[u - 1] && a[u + 1] && u != 1 && u != n)
                cnt++;
            if (a[u] && (u == 1 || !a[u - 1]) && (u == n || !a[u + 1]))
                cnt--;

            if (i == n || a[id[i]] != a[id[i + 1]])
                if (ans < cnt)
                    ans = cnt;

            a[u] = 0;
        }
    }

    cout << ans << endl;

    system("pause");

    return 0;
}