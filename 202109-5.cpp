#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define ll long long
const int maxn = 3e5 + 10;
ll mod;

inline ll Add(int x, int y)
{
    x += y;
    return (x < mod) ? x : x - mod;
}

namespace LCT
{
    ll val[maxn], sum[maxn], tag[maxn], siz[maxn];
    int ch[maxn][2], fa[maxn];
    bool laz[maxn];

#define lc ch[u][0]
#define rc ch[u][1]
#define ws(x) (ch[fa[x]][1] == x)
#define isr(x) (ch[fa[x]][1] != x && ch[fa[x]][0] != x) //&&!!!!!!!!!!

    inline void pushtag(int u, int x)
    {
        (val[u] *= x) %= mod;
        (sum[u] *= x) %= mod;
        (tag[u] *= x) %= mod;
    }

    inline void reverse(int u)
    {
        swap(lc, rc);
        laz[u] ^= 1;
    }

    inline void pushup(int u)
    {
        siz[u] = siz[lc] + siz[rc] + 1;
        sum[u] = Add(sum[lc], sum[rc]);
        sum[u] = Add(sum[u], val[u]);
    }

    inline void pushdown(int u)
    {
        if (laz[u])
        {
            reverse(lc), reverse(rc);
            laz[u] = 0;
        }

        if (tag[u] != 1)
        {
            if (lc)
                pushtag(lc, tag[u]);
            if (rc)
                pushtag(rc, tag[u]);
            tag[u] = 1;
        }
    }

    inline void rotate(int u)
    {
        int f = fa[u], ff = fa[f], w = ws(u), wf = ws(f);

        fa[u] = ff;
        if (!isr(f))
            ch[ff][wf] = u;
        fa[ch[u][w ^ 1]] = f;
        ch[f][w] = ch[u][w ^ 1];
        fa[f] = u;
        ch[u][w ^ 1] = f;

        pushup(f);
        pushup(u);
    }

    inline void push(int u)
    {
        if (!isr(u))
            push(fa[u]);
        pushdown(u);
    }

    inline void splay(int u)
    {
        push(u);
        for (int y = fa[u]; !isr(u); rotate(u), y = fa[u])
            if (!isr(y))
                rotate(ws(u) == ws(y) ? y : u);

        pushup(u);
    }

    // 每次更改子树时记得pushup
    inline void access(int u)
    {
        for (int y = 0; u; y = u, u = fa[u])
            splay(u), ch[u][1] = y, pushup(u);
    }

    inline void makeroot(int u)
    {
        access(u);
        splay(u);
        reverse(u);
    }

    // remember!
    inline void split(int x, int y)
    {
        makeroot(x);
        access(y);
        splay(y);
    }

    inline void link(int x, int y)
    {
        makeroot(x);
        fa[x] = y;
    }

    // 首先，这是循环，其次，访问节点要下传标记
    int find_kth(int u, int k)
    {
        while (114514)
        {
            pushdown(u);
            if (siz[lc] >= k)
                u = lc;
            else
            {
                k -= siz[lc] + 1;
                if (!k)
                    return u;
                u = rc;
            }
        }
    }

    // remember!!! val 为 ll
    inline void update(int u, int l, int r, ll v)
    {
        split(1, u);
        l = find_kth(u, l + 1), r = find_kth(u, r + 1);
        split(l, r);
        pushtag(r, v);
    }

    inline ll query(int u, int l, int r)
    {
        split(1, u);
        l = find_kth(u, l + 1), r = find_kth(u, r + 1);
        split(l, r);
        return sum[r];
    }
}
using namespace LCT;

int m, Fa[maxn], pos[maxn];
ll T, res = 0;

int main()
{
    cin >> m >> mod >> T;
    ll opt, x, s, l, r, y, u = 1, p = 1;
    tag[u] = 1;
    for (int i = 1; i <= m; i++)
    {
        cin >> opt;
        // 记得每天更新pos
        if (opt == 1)
        {
            cin >> x;
            x ^= (T * res);
            if (x == 0)
                p = Fa[p]; // remeber Fa!!!!!!!
            else
            {
                ++u;
                val[u] = x;
                sum[u] = x;
                tag[u] = 1;
                Fa[u] = p;
                link(u, p);
                p = u;
            }
            pos[i] = p; // remember
        }
        else if (opt == 2)
        {
            cin >> s >> l >> r >> y;
            y ^= (T * res);
            update(pos[s], l, r, y);
            pos[i] = pos[i - 1];
        }
        else
        {
            cin >> s >> l >> r;
            res = query(pos[s], l, r);
            cout << res << endl;
            pos[i] = pos[i - 1];
        }
    }

    return 0;
}
