#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <vector>
#define ll long long
using namespace std;

const int maxn = 5e4 + 10;
const int INF = 1e9 + 10;

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

#define ls u << 1
#define rs u << 1 | 1

struct Node
{
    int l, r, id, cnt, laz, mn, mx;
} t[maxn << 4];

struct Oprt
{
    Oprt(int tt, int idd, string L, string R, string S) : type(tt), id(idd), l(L), r(R), s(S) {}
    int type, id, lr, rr, sr;
    string l, r, s;
};

vector<Oprt> oprt;
vector<string> cord;
int c, n, q, m = 0;

inline void pushup(int u)
{
    if (t[ls].id == t[rs].id)
        t[u].id = t[ls].id;
    else
        t[u].id = INF;

    t[u].cnt = t[ls].cnt + t[rs].cnt;
    t[u].mx = max(t[ls].mx, t[rs].mx);
    t[u].mn = min(t[ls].mn, t[rs].mn);
}

inline void pushdown(int u)
{
    if (t[u].l == t[u].r)
        return;
    if (t[u].id != INF)
        t[ls].id = t[rs].id = t[u].id;

    if (t[u].laz)
    {
        t[ls].laz = t[rs].laz = t[u].laz;
        t[ls].cnt = t[ls].r - t[ls].l + 1;
        t[rs].cnt = t[rs].r - t[rs].l + 1;
        t[ls].mx = t[ls].mn = t[u].laz;
        t[rs].mx = t[rs].mn = t[u].laz;
        t[u].laz = 0;
    }
}

inline void build(int u, int l, int r)
{
    t[u] = {l, r, 0, 0, 0, (int)1e9, (int)-1e9};
    if (l == r)
        return;

    int mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);

    pushup(u);
}

inline void query_1(int u, int l, int r, int id, Node &res)
{
    if (t[u].l == l && t[u].r == r)
    {
        res.cnt += t[u].cnt;
        res.mn = min(res.mn, t[u].mn);
        res.mx = max(res.mx, t[u].mx);
        return;
    }

    pushdown(u);

    int mid = t[u].l + t[u].r >> 1;

    if (l <= mid)
        query_1(ls, l, min(mid, r), id, res);
    if (r > mid)
        query_1(rs, max(mid + 1, l), r, id, res);
    return;
}

inline int query_2(int u, int s)
{
    if (t[u].l == t[u].r)
        return t[u].id;

    pushdown(u);

    int mid = t[u].l + t[u].r >> 1;

    if (s <= mid)
        return query_2(ls, s);
    else
        return query_2(rs, s);
}

inline bool query_3(int u, int l, int r)
{
    if (t[u].l == l && t[u].r == r)
    {
        if (t[u].id == INF)
            return false;
        else
        {
            c = t[u].id;
            return true;
        }
    }

    pushdown(u);

    int mid = t[u].l + t[u].r >> 1;
    bool available = true;

    if (l <= mid)
        available &= query_3(ls, l, min(r, mid));
    if (r > mid)
        available &= query_3(rs, max(mid + 1, l), r);

    return available;
}

inline void update(int u, int l, int r, int id)
{
    if (t[u].l == l && t[u].r == r)
    {
        t[u].mn = t[u].mx = id;
        t[u].cnt = t[u].r - t[u].l + 1;
        t[u].laz = id;
        return;
    }

    pushdown(u);

    int mid = t[u].l + t[u].r >> 1;

    if (l <= mid)
        update(ls, l, min(mid, r), id);
    if (r > mid)
        update(rs, max(mid + 1, l), r, id);

    pushup(u);
}

char carry(char ch)
{
    if (ch == '9')
        return 'a';
    else if (ch == 'f')
        return '0';
    return ch + 1;
}

string add(string s)
{
    for (int i = s.size() - 1; i >= 0; i--)
    {
        if (s[i] == ':')
            continue;
        s[i] = carry(s[i]);
        if (s[i] != '0')
            break;
    }
    return s;
}

void discretization()
{
    sort(cord.begin(), cord.end());
    m = unique(cord.begin(), cord.end()) - cord.begin();
    cord.resize(m);
    for (auto &op : oprt)
    {
        if (op.type == 1 || op.type == 3)
        {
            op.lr = lower_bound(cord.begin(), cord.end(), op.l) - cord.begin() + 1;
            op.rr = lower_bound(cord.begin(), cord.end(), op.r) - cord.begin() + 1;
        }
        else
            op.sr = lower_bound(cord.begin(), cord.end(), op.s) - cord.begin() + 1;
    }

    return;
}

// end here

int main()
{
#ifndef ONLINE_JUDGE
    freopen("data/in.in", "r", stdin);
    freopen("data/out.out", "w", stdout);
#endif
    clock_t c1 = clock();
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // Write your code below :)

    cin >> n >> q;
    int type, id;
    string l, r, s;

    for (int i = 1; i <= q; i++)
    {
        cin >> type;
        if (type == 1)
        {
            cin >> id >> l >> r;
            oprt.emplace_back(type, id, l, r, " ");
        }
        else if (type == 2)
        {
            cin >> s;
            oprt.emplace_back(type, id, " ", " ", s);
        }
        else
        {
            cin >> l >> r;
            oprt.emplace_back(type, 0, l, r, " ");
        }

        if (type == 1 || type == 3)
            cord.push_back(l), cord.push_back(r), cord.push_back(add(r));
        else
            cord.push_back(s), cord.push_back(add(s));
    }

    discretization();
    build(1, 1, m);

    for (auto &op : oprt)
    {

        if (op.type == 1)
        {
            Node res({op.lr, op.rr, op.id, 0, (int)1e9, (int)-1e9});
            query_1(1, op.lr, op.rr, op.id, res);

            if (res.cnt == 0 || (res.cnt < res.r - res.l + 1 && res.mn == res.mx == res.id))
            {
                cout << "YES" << endl;
                update(1, op.lr, op.rr, op.id);
            }
            else
                cout << "NO" << endl;
        }
        else if (op.type == 2)
            cout << query_2(1, op.sr) << endl;
        else
        {
            if (query_3(1, op.lr, op.rr))
                cout << c << endl;
            else
                cout << 0 << endl;
        }
    }

    // end here

    cerr << "Time:" << clock() - c1 << endl;

    return 0;
}