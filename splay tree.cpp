#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1e5 + 10;
const int INF = 1e7 + 10;
int n, m, root, ind = 0, a[maxn];

struct Node
{
    int f, laz, val, siz;
    int s[2];

    void init(int v, int fa)
    {
        siz = 1, val = v, f = fa;
    }
} node[maxn];

inline void setson(int son, int fa, int w)
{
    node[fa].s[w] = son;
    node[son].f = fa;
}

inline bool ws(int p)
{
    return node[node[p].f].s[1] == p;
}

inline void pushup(int p)
{
    node[p].siz = node[node[p].s[0]].siz + node[node[p].s[1]].siz + 1;
}

inline void pushdown(int p)
{
    if (node[p].laz)
    {
        node[node[p].s[0]].laz ^= 1;
        node[node[p].s[1]].laz ^= 1;
        node[p].laz = 0;
        swap(node[p].s[0], node[p].s[1]);
    }
}

inline void rotate(int p)
{
    int f = node[p].f, ff = node[f].f, w = ws(p), wf = ws(f);
    pushdown(p), pushdown(f);

    setson(node[p].s[w ^ 1], f, w);
    setson(p, ff, wf);
    setson(f, p, w ^ 1);

    pushup(f);
    pushup(p);
}

inline void splay(int p, int to)
{
    for (int qwq; (qwq = node[p].f) != to; rotate(p))
        if (node[qwq].f != to)
            rotate(ws(p) == ws(qwq) ? qwq : p);

    if (to == 0)
        root = p;
}

inline void insert(int v)
{
    int x = root, fa = 0;
    while (x)
    {
        fa = x;
        x = node[x].s[v > node[x].val];
    }

    x = ++ind;
    if (fa)
        node[fa].s[v > node[fa].val] = x;

    node[x].init(v, fa);

    splay(x, 0);
}

int find(int x)
{
    int p = root;
    while (114514)
    {
        pushdown(p);

        if (x <= node[node[p].s[0]].siz)
            p = node[p].s[0];
        else
        {
            x -= node[node[p].s[0]].siz + 1;
            if (!x)
                return p;
            p = node[p].s[1];
        }
    }
}

inline void reverse(int l, int r)
{
    l = find(l - 1), r = find(r + 1);
    splay(l, 0);
    splay(r, l);
    int p = node[node[root].s[1]].s[0];
    node[p].laz ^= 1;
}

inline void dfs(int p)
{
    pushdown(p);
    if (node[p].s[0])
        dfs(node[p].s[0]);
    if (abs(node[p].val) != INF)
        cout << node[p].val << " ";
    if (node[p].s[1])
        dfs(node[p].s[1]);
}

int main()
{
    cin >> n >> m;

    insert(-INF);
    for (int i = 1; i <= n; i++)
        insert(i);
    insert(INF);

    for (int i = 1; i <= m; i++)
    {
        int l, r;
        cin >> l >> r;
        reverse(l + 1, r + 1);
    }
    dfs(root);

    return 0;
}