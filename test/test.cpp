/*
Name: enemy(HDU1166)
Author: godwings
Date: 26/09/2017
*/
#include <cctype>
#include <cstdio>
#include <cstring>
const int kMaxN = 50010;
const int kMaxM = 40010;
const int kMaxO = (kMaxM << 1) + kMaxN;

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

int T, n;
char op[10];
int ans[kMaxM];

struct Operate {
    int type;
    int pos, del;
    Operate(const int type_, const int pos_, const int del_) {
        type = type_;
        pos = pos_;
        del = del_;
    }
}ope[kMaxO]; int m;

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("enemy.in", "r", stdin);
    freopen("enemy.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(T);
    for (int t = 1; t <= T; t++) {
        scan(n);
        m = 0;
        memset(ans, 0, sizeof ans);

    }
    return 0;
}
