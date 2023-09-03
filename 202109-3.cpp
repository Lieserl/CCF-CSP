#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 1e3 + 10;

struct Edge
{
    Edge(int t, double w, int d) : to(t), val(w), D(d) {}

    int to, D;
    double val;
};

vector<Edge> s[2010];
int N, S, P, T, R, r[maxn], sum[maxn];
double dt, u[maxn], v[maxn], a[maxn], b[maxn], c[maxn], d[maxn], sim[maxn][maxn];
static unsigned long nex = 1;

/* RAND_MAX assumed to be 32767 */
int myrand(void)
{
    nex = nex * 1103515245 + 12345;
    return ((unsigned)(nex / 65536) % 32768);
}

int main()
{
    scanf("%d%d%d%d%lf", &N, &S, &P, &T, &dt);

    int sum_n = 0, g = 0;
    while (sum_n < N)
    {
        scanf("%d", &R);
        scanf("%lf%lf%lf%lf%lf%lf", &v[g], &u[g], &a[g], &b[g], &c[g], &d[g]);
        g++; // 勿忘
        for (int i = 1; i < R; i++, g++)
            v[g] = v[g - 1], u[g] = u[g - 1], a[g] = a[g - 1], b[g] = b[g - 1], c[g] = c[g - 1], d[g] = d[g - 1];
        sum_n += R;
    }

    for (int i = 0; i < P; i++)
        scanf("%d", &r[i]);

    // 此处模拟的是突触，也就是边
    for (int i = 0; i < S; i++)
    {
        int start, e, D;
        double w;
        scanf("%d%d%lf%d", &start, &e, &w, &D);
        s[start].push_back({e, w, D});
    }

    for (int t = 1; t <= T; t++)
    {
        int temp = t % 1000;
        for (int i = 0; i < N; i++)
        {
            double pre_v = v[i];
            v[i] = v[i] + dt * (v[i] * (0.04 * v[i] + 5) + 140 - u[i]) + sim[temp][i];
            u[i] = u[i] + dt * a[i] * (b[i] * pre_v - u[i]);
            sim[temp][i] = 0; // 记得清空
            if (v[i] >= 30)
            {
                // 忘写了qaq
                sum[i]++;
                v[i] = c[i];
                u[i] += d[i];
                for (auto &j : s[i])
                    sim[(t + j.D) % 1000][j.to] += j.val; // 不能用temp代替取模
            }
        }

        for (int i = 0; i < P; i++)
            if (r[i] > myrand())
                for (auto &j : s[N + i])
                    sim[(t + j.D) % 1000][j.to] += j.val;
    }

    double min_v = v[0], max_v = v[0];
    int maxx = sum[0], minn = sum[0];

    for (int i = 0; i < N; i++)
    {
        maxx = max(maxx, sum[i]);
        minn = min(minn, sum[i]);
        min_v = min(min_v, v[i]);
        max_v = max(max_v, v[i]);
    }

    printf("%.3f %.3f\n%d %d", min_v, max_v, minn, maxx);
    system("pause");
    return 0;
}