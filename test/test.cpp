/*
Name: fighting(LJOJ4520)
Author: godwings
Date: 18/09/2017
*/
#include <cctype>
#include <cstdio>
const int kMaxN = 60;
const int kMaxM = 3000;
typedef long double LD;

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
    template <class T>
    inline void scan(T &x, T &y) {
        scan(x); scan(y);
    }
    template <class T>
    inline void scan(T &x, T &y, T &z) {
        scan(x); scan(y); scan(z);
    }
}  // namespace FastIO
using FastIO::scan;

int n, m;
LD r, p_start, p_end, ev_start, ev_end;
LD p[kMaxN][kMaxN][kMaxM], ev[kMaxN][kMaxN][kMaxM];

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("fighting.in", "r", stdin);
    freopen("fighting.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(n, m);
    scanf("%LF", &r);
    p[0][0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= i * j; k++) {
                if (i == n && j == m) {
                    p_end += p[i][j][k];
                    ev_end += ev[i][j][k];
                    continue;
                }
                LD all = n * m, x;
                LD now_p = p[i][j][k], now_ev = ev[i][j][k];
                // do nothing
                x = k / all * (1 - r);
                now_ev += now_p / (1 - x);
                all -= k * (1 - r);
                // be sad
                x = k / all * r;
                p_start += x * now_p;
                ev_start += x * (now_ev - now_p);
                // new green
                x = (n - i) * j / all;
                p[i + 1][j][k + 1] += x * now_p;
                ev[i + 1][j][k + 1] += x * now_ev;
                // new red
                x = i * (m - j) / all;
                p[i][j + 1][k + 1] += x * now_p;
                ev[i][j + 1][k + 1] += x * now_ev;
                // new both
                x = (n - i) * (m - j) / all;
                p[i + 1][j + 1][k + 1] += x * now_p;
                ev[i + 1][j + 1][k + 1] += x * now_ev;
                // new neither
                x = (i * j - k) / all;
                p[i][j][k + 1] += x * now_p;
                ev[i][j][k + 1] += x * now_ev;
            }
        }
    }
    printf("%.6LF\n", ev_end / p_end + ev_start / p_end);
    return 0;
}
