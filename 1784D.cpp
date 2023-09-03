#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cstdio>
#define ll long long
using namespace std;

const int maxn = 1050000;
const int mod = 998244353;

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

ll n, N, fac[maxn], ifac[maxn], dp[23][maxn], sum[23][maxn];

inline ll q_pow(ll x, ll p)
{
    ll res = 1;
    while (p)
    {
        if (p & 1)
            res = (res * x) % mod;
        x = x * x % mod;
        p = p >> 1;
    }

    return res;
}

inline void cal_fac()
{
    fac[0] = 1;
    for (int i = 1; i <= N; i++)
        fac[i] = fac[i - 1] * i % mod;

    ifac[N] = q_pow(fac[N], mod - 2);
    for (int i = N - 1; i >= 0; i--)
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

inline ll c(ll m, ll n)
{
    if (m < 0 || n < 0 || m > n)
        return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

// end here

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // Write your code below :)

    cin >> n;
    N = 1 << n, dp[0][0] = 1;
    cal_fac();

    for (ll i = 0; i <= N; i++)
        sum[0][i] = 1;

    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= N; j++)
        {
            dp[i][j] = 2 * fac[1 << (n - i)] % mod * c((1 << (n - i)) - 1, N - (1 << (n - i)) - j) % mod * sum[i - 1][j - 1] % mod;
            sum[i][j] = (sum[i][j - 1] + dp[i][j]) % mod;
        }

    for (ll i = 1; i <= N; i++)
        cout << sum[n][i - 1] << endl;

    // end here

    return 0;
}