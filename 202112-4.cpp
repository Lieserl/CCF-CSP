#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 8e5 + 10;
const int INF = 1e9 + 10;

struct Node
{
    int l, r;
    int val, id, state;
} t[maxn << 2];

struct operation
{
    operation(int tt, int idd, int ll, int rr, int xx, int pp) : type(tt), id(idd), l(ll), r(rr), x(xx), p(pp) {}
    int type, id, l, r, x, p;
};

int m, n, k;
vector<operation> oprt;
vector<int> cord;

inline int ls(int p)
{
    return p << 1;
}

inline int rs(int p)
{
    return p << 1 | 1;
}

inline void pushup(int p)
{
    if (t[ls(p)].id == t[rs(p)].id)
        t[p].id = t[ls(p)].id;
    else
        t[p].id = INF;

    if (t[ls(p)].val == t[rs(p)].val)
        t[p].val = t[ls(p)].val;
    else
        t[p].val = INF;

    if (t[ls(p)].state == t[rs(p)].state)
        t[p].state = t[ls(p)].state;
    else
        t[p].state = INF;
}

// 啊啊啊啊啊，你在复制粘贴写啥啊啊啊啊
inline void pushdown(int p)
{
    if (t[p].l == t[p].r)
        return;
    if (t[p].id != INF)
        t[ls(p)].id = t[rs(p)].id = t[p].id;
    if (t[p].val != INF)
        t[ls(p)].val = t[rs(p)].val = t[p].val;
    if (t[p].state != INF)
        t[ls(p)].state = t[rs(p)].state = t[p].state;
}

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if (l == r)
        return;
    int mid = t[p].l + t[p].r >> 1;

    // 你在写什么啊啊啊啊啊
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);

    pushup(p);
}

inline int find_right(int p, int l, int id)
{
    if (t[p].state == 0 || t[p].state == 2 || t[p].id == id)
        return t[p].r;
    else if (t[p].state == 1 && t[p].id != INF)
        return -INF;

    int mid = t[p].l + t[p].r >> 1;
    pushdown(p);

    if (l <= mid)
    {
        int lr = find_right(ls(p), l, id);
        if (lr < mid)
            return lr;
        int rr = find_right(rs(p), l, id);
        if (rr == -INF)
            return lr;
        return rr;
    }
    else
        return find_right(rs(p), l, id);
}

void update(int curr, int to_l, int to_r, int id, int x)
{
    if (t[curr].l == to_l && t[curr].r == to_r)
    { // 刚好覆盖
        t[curr].state = 1;
        t[curr].id = id;
        t[curr].val = x;
        return;
    }
    int mid = t[curr].l + ((t[curr].r - t[curr].l) >> 1);
    pushdown(curr);
    if (to_l <= mid)
        update(curr << 1, to_l, min(to_r, mid), id, x);
    if (to_r > mid)
        update(curr << 1 | 1, max(to_l, mid + 1), to_r, id, x);
    pushup(curr);
};

bool is_deletion(int p, int l, int r, int id)
{
    if (t[p].l == l && t[p].r == r)
    {
        if (t[p].state == 1 && t[p].id == id)
            return true;
        else
            return false;
    }

    int mid = t[p].l + t[p].r >> 1;
    pushdown(p);

    bool available = true;
    if (l <= mid)
        available &= is_deletion(ls(p), l, min(r, mid), id);
    if (r > mid)
        available &= is_deletion(rs(p), max(mid + 1, l), r, id);
    return available;
}

inline void deletion(int p, int l, int r, int id)
{
    if (t[p].l == l && t[p].r == r)
    {
        t[p].state = 2;
        return;
    }

    int mid = t[p].l + t[p].r >> 1;
    pushdown(p);

    if (l <= mid)
        deletion(ls(p), l, min(r, mid), id);
    if (r > mid)
        deletion(rs(p), max(l, mid + 1), r, id);

    pushup(p);
}

bool is_recover(int p, int l, int r, int id)
{
    if (t[p].l == l && t[p].r == r)
    {
        if (t[p].state == 2 && t[p].id == id)
            return true;
        else
            return false;
    }

    int mid = t[p].l + t[p].r >> 1;
    pushdown(p);

    bool available = true;
    if (l <= mid)
        available &= is_recover(ls(p), l, min(r, mid), id);
    if (r > mid)
        available &= is_recover(rs(p), max(mid + 1, l), r, id);
    return available;
}

inline void recover(int p, int l, int r, int id)
{
    if (t[p].l == l && t[p].r == r)
    {
        t[p].state = 1;
        return;
    }

    int mid = t[p].l + t[p].r >> 1;
    pushdown(p);

    if (l <= mid)
        recover(ls(p), l, min(r, mid), id);
    if (r > mid)
        recover(rs(p), max(l, mid + 1), r, id);

    pushup(p);
}

inline int query(int p, int pos)
{
    if (t[p].l == t[p].r)
        return p;
    else if (t[p].id != INF && t[p].val != INF && t[p].state != INF)
        return p;

    // 别忘了pushdown
    int mid = t[p].l + t[p].r >> 1;
    pushdown(p);
    if (pos <= mid)
        return query(ls(p), pos);
    else
        return query(rs(p), pos);
}

void discretization()
{
    cord.push_back(0);
    sort(cord.begin(), cord.end());
    m = unique(cord.begin(), cord.end()) - cord.begin();
    cord.resize(m);
    for (auto &op : oprt)
    {
        if (op.type == 0 || op.type == 1 || op.type == 2)
        {
            op.l = lower_bound(cord.begin(), cord.end(), op.l) - cord.begin() + 1;
            op.r = lower_bound(cord.begin(), cord.end(), op.r) - cord.begin() + 1;
        }
        else
            op.p = lower_bound(cord.begin(), cord.end(), op.p) - cord.begin() + 1;
    }
    return;
}

int main()
{
    cin >> n >> m >> k;
    int type, id, l, r, x, p;
    for (int i = 0; i < k; i++)
    {
        cin >> type;
        if (type == 0)
        {
            scanf("%d%d%d%d", &id, &l, &r, &x);
            oprt.emplace_back(type, id, l, r, x, 0);
        }
        else if (type == 1)
        {
            scanf("%d%d%d", &id, &l, &r);
            oprt.emplace_back(type, id, l, r, 0, 0);
        }
        else if (type == 2)
        {
            scanf("%d%d%d", &id, &l, &r);
            oprt.emplace_back(type, id, l, r, 0, 0);
        }
        else
        {
            scanf("%d", &p);
            oprt.emplace_back(type, 0, 0, 0, 0, p);
        }

        if (type == 0 || type == 1 || type == 2)
        {
            cord.push_back(l), cord.push_back(r);
            if (l != 1)
                cord.push_back(l - 1);
            if (r != m)
                cord.push_back(r + 1);
        }
        else
            cord.push_back(p);
    }

    discretization();
    build(1, 1, m - 1); // m个元素，再排除0

    int indexx;
    for (auto &op : oprt)
    {
        if (op.type == 0)
        {
            op.r = min(op.r, find_right(1, op.l, op.id));
            if (op.r != -INF)
                update(1, op.l, op.r, op.id, op.x);
            printf("%d\n", op.r == -INF ? -1 : cord[op.r]);
        }
        else if (op.type == 1)
        {
            if (is_deletion(1, op.l, op.r, op.id))
            {
                deletion(1, op.l, op.r, op.id);
                printf("OK\n");
            }
            else
                printf("FAIL\n");
        }
        else if (op.type == 2)
        {
            if (is_recover(1, op.l, op.r, op.id))
            {
                recover(1, op.l, op.r, op.id);
                printf("OK\n");
            }
            else
                printf("FAIL\n");
        }
        else
        {
            indexx = query(1, op.p);
            if (t[indexx].state != 1)
                printf("0 0\n");
            else
                printf("%d %d\n", t[indexx].id, t[indexx].val);
        }
    }

    system("pause");

    return 0;
}

// int main()
// {
//     scanf("%d%d%d", &n, &m, &k);
//     int type = 0, id = 0, l = 0, r = 0, x = 0, p = 0;
//     for (int i = 0; i < k; i++)
//     {
//         scanf("%d", &type);
//         switch (type)
//         {
//         case 0:
//             scanf("%d%d%d%d", &id, &l, &r, &x);
//             oprt.emplace_back(type, id, l, r, x, 0);
//             break;
//         case 1:
//             scanf("%d%d%d", &id, &l, &r);
//             oprt.emplace_back(type, id, l, r, 0, 0);
//             break;
//         case 2:
//             scanf("%d%d%d", &id, &l, &r);
//             oprt.emplace_back(type, id, l, r, 0, 0);
//             break;
//         case 3:
//             scanf("%d", &p);
//             oprt.emplace_back(type, 0, 0, 0, 0, p);
//             break;
//         default:
//             break;
//         }
//         if (type == 0 || type == 1 || type == 2)
//         {
//             cord.push_back(l);
//             cord.push_back(r);
//             if (l != 1)
//                 cord.push_back(l - 1); // 注意离散化要加入前后的点
//             if (r != m)
//                 cord.push_back(r + 1);
//         }
//         else
//         {
//             cord.push_back(p);
//         }
//     }
//     /* 离散化 */
//     discretization();
//     /* 建树 */
//     build(1, 1, m - 1);
//     int query_index;
//     for (auto &op : oprt)
//     {
//         switch (op.type)
//         {
//         case 0:
//             op.r = min(op.r, find_right(1, op.l, op.id));
//             if (op.r != -INF)
//                 update(1, op.l, op.r, op.x, op.id);
//             printf("%d\n", op.r == -INF ? -1 : cord[op.r]);
//             break;
//         case 1:
//             if (is_deletion(1, op.l, op.r, op.id))
//             {
//                 deletion(1, op.l, op.r, op.id);
//                 printf("OK\n");
//             }
//             else
//             {
//                 printf("FAIL\n");
//             }
//             break;
//         case 2:
//             if (is_recover(1, op.l, op.r, op.id))
//             {
//                 recover(1, op.l, op.r, op.id);
//                 printf("OK\n");
//             }
//             else
//                 printf("FAIL\n");
//             break;
//         case 3:
//             query_index = query(1, op.p);
//             if (t[query_index].state != INF)
//                 printf("%d %d\n", 0, 0);
//             else
//                 printf("%d %d\n", t[query_index].id, t[query_index].val);
//             break;
//         default:
//             break;
//         }
//     }

//     system("pause");

//     return 0;
// }
