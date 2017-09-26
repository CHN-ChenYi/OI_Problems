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
    Operate() {
        type = pos = del = 0;
    }
    Operate(const int type_, const int pos_) {
        type = type_;
        pos = pos_;
    }
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
        for (int i = 1, x; i <= n; i++) {
            scan(x);
            ope[++m] = Operate(0, i, x);
        }
        while (true) {
            scanf("%s", op);
            if (op[0] == 'E') {
                break;
            } else if (op[0] == 'Q') {
                int l, r;
                scan(l, r);
                ope[++m] = Operate(-1, l - 1);
                ope[++m] = Operate(1, r);
            } else {
                int pos, del;
                scan(pos, del);
                del *= (op[0] == 'A' ? 1 : -1);
                ope[++m] = Operate(0, pos, del);
            }
        }
    }
    return 0;
}
