/*
Name: economic(LJOJ4548)
Author: godwings
Date: 01/10/2017
*/
#include <cctype>
#include <cstdio>
#include <vector>
#include <algorithm>
using std::max;
using std::vector;
const int kMaxN = 20;

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

int T;
int n;
double W;
int a[kMaxN];

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("economic.in", "r", stdin);
    freopen("economic.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(T);
    while (T--) {
        scanf("%lf", &W); scan(n);
        for (int i = 1; i <= n; i++)
            scan(a[i]);

    }
    return 0;
}
