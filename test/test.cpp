/*
Name: title(sourceNo)
Author: godwings
Date: DD/MM/YYYY
*/
#include <cstdio>

#include <cctype>
namespace FastIO {
    template <class T>
    inline void scan(T &x) {
        x = 0;
        char c;
        bool positive = 1;
        while (!isdigit(c = getchar())) {
            if (!positive) positive = 1;
            if (c == '-') positive = 0;
        }
        while (isdigit(c)) {
            x = x * 10 + (c & 0xf);
            c = getchar();
        }
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

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("title.in", "r", stdin);
    freopen("title.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif

    return 0;
}
