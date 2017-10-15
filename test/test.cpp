/*
Name: strings(LJOJ4561)
Author: godwings
Date: 15/10/2017
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
    inline void scan(char &x) {
        while (!isgraph(x = getchar())) { }
    }
    inline void scan(double &x) {
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
        if (c == '.') {
            double now = 0.1;
            c = getchar();
            while (isdigit(c)) {
                x += now * (c & 0xf);
                now *= 0.1;
                c = getchar();
            }
        }
        if (!positive)
            x *= -1;
    }
    template <class T_1, class T_2>
    inline void scan(T_1 &a, T_2 &b) {
        scan(a); scan(b);
    }
    template <class T_1, class T_2, class T_3>
    inline void scan(T_1 &a, T_2 &b, T_3 &c) {
        scan(a); scan(b); scan(c);
    }
    template <class T_1, class T_2, class T_3, class T_4>
    inline void scan(T_1 &a, T_2 &b, T_3 &c, T_4 &d) {
        scan(a); scan(b); scan(c); scan(d);
    }
}  // namespace FastIO
using FastIO::scan;

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("strings.in", "r", stdin);
    freopen("strings.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif  // ONLINE_JUDGE

    return 0;
}
