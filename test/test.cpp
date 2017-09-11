/*
Name: K-th(POJ2104)
Author: godwings
Date: 11/09/2017
*/
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int kMaxN = 100010;
using std::nth_element;

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
int a[kMaxN], b[kMaxN];

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("K-th.in", "r", stdin);
    freopen("K-th.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(n, m);
    for (int i = 1; i <= n; i++)
        scan(a[i]);
    for (int i = m, l, r, k; i; i--) {
        scan(l, r, k);
        const int len = r - l + 1;
        memcpy(b, a + l, len * sizeof(int));
        nth_element(b, b + k - 1, b + len);
        printf("%d\n", b[k - 1]);
    }
    return 0;
}
