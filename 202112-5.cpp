#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 5e5 + 10;
const int INF = 1e9 + 10;

vector<int> s[maxn];
int root = 0, maxp[maxn], siz[maxn], vis[maxn], Sum = 0;
int n, K1, K2;

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

inline void getrt(int u, int fa)
{
    siz[u] = 1, maxp[u] = 0;
    for (auto &v : s[u])
    {
        if (vis[v] || v == fa)
            continue;
        getrt(v, u);
        siz[u] += siz[v];
        maxp[u] = max(maxp[u], siz[v]);
    }
    maxp[u] = max(maxp[u], Sum - siz[u]);
    if (maxp[u] < maxp[root])
        root = u;
}

inline void getm(int u, int fa, vector<int> &nodes, pair<int, int> *value, int mn, int mx)
{
    nodes.push_back(u);
    value[u].first = mn, value[u].second = mx;
    for (auto &v : s[u])
    {
        if (vis[v] || v == fa)
            continue;
        getm(v, u, nodes, value, min(mn, v), max(mx, v));
    }
}

// 可持久化线段树
struct node
{
    int siz, l, r;
} sz[maxn * 20];

int indexx = 0, rt[maxn];

// 别忘了写出口
inline void insert(int l, int r, int pre, int &now, int p)
{
    sz[++indexx] = sz[pre];
    now = indexx, sz[now].siz++;
    if (l >= r)
        return;

    int mid = l + r >> 1;
    if (p <= mid)
        insert(l, mid, sz[pre].l, sz[now].l, p);
    else
        insert(mid + 1, r, sz[pre].r, sz[now].r, p);
}

inline int query(int l, int r, int now, int p)
{
    if (l >= r)
        return sz[now].siz;

    int mid = l + r >> 1;

    if (p <= mid)
        return query(l, mid, sz[now].l, p);
    else
        return sz[sz[now].l].siz + query(mid + 1, r, sz[now].r, p);
}

// 记得开 long long
inline long long solve(int u, int mn, int mx)
{
    vector<int> nodes;
    static pair<int, int> value[maxn];
    static int w[maxn];

    getm(u, 0, nodes, value, min(mn, u), max(mx, u));
    for (int i = 1; i <= nodes.size(); i++)
        w[i] = nodes[i - 1];
    sort(w + 1, w + nodes.size() + 1);

    long long cnt = 0;
    indexx = 0, rt[0] = 0;
    for (int i = 1; i <= nodes.size(); i++)
    {
        auto p = value[w[i]];
        rt[i] = rt[i - 1];
        if (w[i] - K1 <= p.first)
            // 1你写个 i 作甚
            insert(1, n, rt[i - 1], rt[i], p.second);
        // 不是 else if !!!!!!!!!!!!!!
        if (w[i] + K2 >= p.second)
        {
            int nv = p.first + K1;
            // 只能查i + 1以前的
            int pos = min(int(upper_bound(w + 1, w + nodes.size() + 1, nv) - w - 1), i);
            if (pos >= 1)
                // 找小于等于 w[i] + K2的
                cnt += query(1, n, rt[pos], w[i] + K2);
        }
    }

    return cnt;
}

long long ans = 0;
inline void divide(int u)
{
    // 先计算后标记
    ans += solve(u, INF, 0);
    vis[u] = true;
    for (auto &v : s[u])
    {
        if (vis[v])
            continue;
        ans -= solve(v, u, u);
        Sum = siz[v];
        maxp[root = 0] = INF;
        // 每一次重新找重心
        getrt(v, 0);
        divide(root);
    }
}

int main()
{
    scanf("%d%d%d", &n, &K1, &K2);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        u = read();
        v = read();
        s[u].push_back(v);
        s[v].push_back(u);
    }
    maxp[root = 0] = INF;
    Sum = n;
    getrt(1, 0);
    divide(root);

    printf("%lld", ans);

    return 0;
}
