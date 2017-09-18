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
LD r, pstart, pend, evstart, evend;
LD f[kMaxN][kMaxN][kMaxM], g[kMaxN][kMaxN][kMaxM];

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
    scanf("%lf", r);

    return 0;
}
