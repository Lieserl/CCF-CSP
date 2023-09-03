#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <vector>
#define ll long long
using namespace std;

const int maxn = 1e2 + 10;

inline int read()
{
    int f = 1, k = 0;
    char c = getchar();

    while (c < '0' || c > '9')
        c = getchar();

    while (c >= '0' && c <= '9')
    {
        k = k * 10 + c - '0';
        c = getchar();
    }

    return f * k;
}

// Write your code below :)
struct Edge
{
    Edge(int t, int v) : to(t), val(v) {}
    int to, val;
};

vector<Edge> s[maxn];
bool req[maxn][20], flag[maxn];
ll N, M, K, dp[maxn], f[maxn][1 << 12], initial[maxn][20];

inline ll dfs(int u, int fa)
{
    ll maxx = 0;
    for (auto &v : s[u])
    {
        if (v.to == fa)
            continue;
        ll temp = dfs(v.to, u);

        if (flag[v.to])
        {
            flag[u] = true;
            dp[u] += dp[v.to] + v.val * 2;
            maxx = max(maxx, temp + v.val);
        }
    }

    return maxx;
}

// end here

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // Write your code below :)

    cin >> N >> M >> K;
    int u, v, w;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= K; j++)
            cin >> req[i][j];

    for (int i = 1; i < N; i++)
    {
        cin >> u >> v >> w;
        s[u].emplace_back(v, w);
        s[v].emplace_back(u, w);
    }

    for (int i = 1; i <= K; i++)
        for (int j = 1; j <= N; j++)
        {
            memset(dp, 0, sizeof(dp));
            memset(flag, false, sizeof(flag));

            for (int k = 1; k <= N; k++)
                flag[k] = req[k][i];

            ll dis = dfs(j, 0);
            initial[j][i] = dp[j] - dis;
        }

    for (int i = 1; i < (1 << K); i++)
    {
        ll minn = 1e19 + 10;
        for (int j = 1; j <= N; j++)
        {
            ll temp = 0;
            for (int k = 1; k <= K; k++)
            {
                if (i & (1 << (k - 1)))
                    temp = max(temp, initial[j][k]);
            }
            minn = min(minn, temp);
        }
        f[1][i] = minn;
    }

    for (int i = 2; i <= M; i++)
        for (int j = 1; j < (1 << K); j++)
        {
            f[i][j] = 1e19 + 10;
            for (int k = j; k; k = (k - 1) & j)
                f[i][j] = min(f[i][j], max(f[1][k], f[i - 1][j ^ k]));
        }

    cout << f[M][(1 << K) - 1] << endl;

    // end here

    return 0;
}