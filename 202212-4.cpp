#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <vector>
#define ll long long
using namespace std;

const int maxn = 1e2 + 10;

struct Edge
{
    Edge(int t, int v) : to(t), val(v) {}
    int to, val;
};

ll dfs(int u, int fa, vector<vector<Edge>> &s, vector<bool> &flag, vector<ll> &dp)
{
    ll maxx = 0;
    for (auto &v : s[u])
    {
        if (v.to == fa)
            continue;
        ll temp = dfs(v.to, u, s, flag, dp);

        if (flag[v.to])
        {
            flag[u] = true;
            dp[u] += dp[v.to] + v.val * 2;
            maxx = max(maxx, temp + v.val);
        }
    }
    return maxx;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N, M, K;
    cin >> N >> M >> K;
    int u, v, w;

    vector<vector<bool>> req(N + 1, vector<bool>(K + 1, false));
    vector<vector<Edge>> s(N + 1);
    vector<vector<ll>> initial(N + 1, vector<ll>(K + 1, 0));
    vector<vector<ll>> f(N + 1, vector<ll>((1 << K) + 1, 0));

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
            vector<ll> dp(N + 1, 0);
            vector<bool> flag(N + 1, false);

            for (int k = 1; k <= N; k++)
                flag[k] = req[k][i];

            ll dis = dfs(j, 0, s, flag, dp);
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

    return 0;
}
