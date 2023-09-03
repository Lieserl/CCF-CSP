#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 1e5 + 10;

struct Edge
{
    int to, next;
} edge[maxn];

struct Node
{
    int l, r;
    long long val;
} t[maxn << 2];

int n, r, tot = 0, res = 0, head[maxn], lazy[maxn << 2];
int tim = 0, fa[maxn], dep[maxn], son[maxn], siz[maxn], top[maxn], dfn[maxn], w[maxn], wn[maxn];

void addEdge(int u, int v)
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void readTree()
{
    int u, v;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> w[i];

    for (int i = 1; i < n; i++)
    {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
}

// 线段树

inline int ls(int x)
{
    return x << 1;
}

inline int rs(int x)
{
    return x << 1 | 1;
}

inline void pushup(int x)
{
    t[x].val = t[ls(x)].val + t[rs(x)].val;
}

inline void build(int p, int ll, int rr)
{
    t[p].l = ll, t[p].r = rr;
    if (ll == rr)
    {
        t[p].val = wn[ll];
        return;
    }

    int mid = ll - (ll - rr) >> 1;
    build(ls(p), ll, mid);
    build(rs(p), mid + 1, rr);

    pushup(p);
}

inline void pushdown(int p)
{
    if (lazy[p])
    {
        lazy[ls(p)] += lazy[p];
        lazy[rs(p)] += lazy[p];

        int mid = t[p].r - (t[p].r - t[p].l) >> 1;

        t[ls(p)].val += lazy[p] * (mid - t[p].l + 1);
        t[rs(p)].val += lazy[p] * (t[p].r - mid);

        lazy[p] = 0;
    }
}

inline int update(int p, int ll, int rr, int x)
{
    if (t[p].l == ll && t[p].r == rr)
    {
        lazy[p] += x;
        t[p].val += x * (t[p].r - t[p].l + 1);
        return;
    }

    if (lazy[p])
        pushdown(p);

    int mid = t[p].r - (t[p].r - t[p].l) >> 1;

    if (ll <= mid)
        update(ls(p), ll, mid, x);
    if (rr > mid)
        update(rs(p), mid + 1, rr, x);
}

inline void query(int p, int ll, int rr)
{
    if (t[p].l == ll && t[p].r == rr)
    {
        res += t[p].val;
        return;
    }

    if (lazy[p])
        pushdown(p);

    int mid = t[p].r - (t[p].r - t[p].l) >> 1;

    if (ll <= mid)
        query(ls(p), ll, mid);
    if (rr > mid)
        query(rs(p), mid + 1, rr);
}

// 树链剖分
inline void dfs1(int u, int f)
{
    fa[u] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    int maxsize = -1;
    for (int i = head[u]; ~i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == f)
            continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > maxsize)
        {
            maxsize = siz[v];
            son[u] = v;
        }
    }
}

inline void dfs2(int u, int topf)
{
    dfn[u] = ++tim;
    wn[tim] = w[u];
    top[u] = topf;
    if (!son[u])
        return;
    dfs2(son[u], topf);
    for (int i = head[u]; ~i; i = edge[i].next)
    {
        if (edge[i].to == fa[u] || edge[i].to == son[u])
            continue;
        dfs2(edge[i].to, edge[i].to);
    }
}

inline int qRange(int x, int y)
{
    int ans = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        res = 0;
        query(1, dfn[top[x]], dfn[x]);
        ans += res;
        x = fa[top[x]];
    }

    if (dep[x] > dep[y])
        swap(x, y);
    res = 0;
    query(1, x, y);
    ans += res;
    return ans;
}

int main()
{
    cin >> n >> r;
    dfs1(r, 0);
    dfs2(r, r);
    build(1, 1, n);

    system("pause");

    return 0;
}