/*
Name: string(LJOJ4505)
Author: godwings
Date: 10/09/2017
*/
#include <cctype>
#include <cstdio>
#include <algorithm>
const int kMaxN = 100010;
typedef long long LL;
const LL inf = 0x7fffffffffffffff;
using std::min;

namespace FastIO {
    template <class T>
    inline void scan(T &x) {
        bool positive = 1;
        char c;
        while (isdigit(c = getchar()) == 0) {
            if (!positive) positive = 1;
            if (c == '-') positive = 0;
        }
        x = 0;
        for (; isdigit(c) != 0; c = getchar())
            x = x * 10 + (c & 0xf);
        if (!positive)
            x *= -1;
    }
    inline void scan(char &x) {
        while (!isalpha(x = getchar())) { }
    }
    template <class T>
    inline void scan(T &x, T &y) {
        scan(x); scan(y);
    }
    template <class T>
    inline void scan(T &x, T &y, T &z) {
        scan(x); scan(y); scan(z);
    }
    template <class T>
    inline void scan(T &a, T &b, T &c, T &d) {
        scan(a); scan(b); scan(c); scan(d);
    }
}  // namespace FastIO
using FastIO::scan;

int n;
char s[kMaxN];
int cnt[kMaxN][26];
int dif[kMaxN], sum[kMaxN];

int a, b;
int c, d, l, r;
int q[kMaxN], pre[kMaxN];
LL f[kMaxN];
inline bool Check(int x, int y) {
    int t = 0;
    for (int i = 0; i < 26; i++)
        if (t < cnt[y][i] - cnt[x - 1][i])
            t = cnt[y][i] - cnt[x - 1][i];
    return t >= l && t <= r;
}
inline void Update(int x, int y) {
    if (y < x && y >= 0)
        f[x] = min(f[x], f[y] + b + 1ll * a * (sum[x] - sum[y]) * (sum[x] - sum[y]));
}

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(n);
    scan(a, b);
    scan(c, d, l, r);
    for (int i = 1; i <= n; i++) {
        scan(s[i]);
        cnt[i][s[i] - 'a'] = 1;
        for (int j = 0; j < 26; j++)
            cnt[i][j] += cnt[i - 1][j];
    }
    for (int i = 1; i <= n; i++) {
        f[i] = inf;
        scan(dif[i]);
        sum[i] = sum[i - 1] + dif[i];
    }
    for (int i = n - 1, j; i >= 1; i--) {
        if (!dif[i])
            continue;
        for (j = 1; !dif[i + j] && i + j <= n; j++)
            pre[i + j] = i;
        if (i + j <= n)
            pre[i + j] = i;
    }

    return 0;
}
