/*
Name: CRB(HDU5412)
Author: godwings
Date: 12/09/2017
*/
#include <cctype>
#include <cstdio>
#include <cstring>
const int inf = 0x3fffffff;
const int kMaxN = 2e5 + 10;

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
struct Operate {
    int id;
    bool type; // 0 for modify, 1 for query
    int pos, key;
    int l, r, k, cnt;
    Operate() {
        memset(this, 0, sizeof(Operate));
    }
    Operate(const int id_, const int pos_, const int key_) {
        id = id_;
        type = 0;
        pos = pos_;
        key = key_;
    }
    Operate(const int id_, const int l_, const int r_, const int k_) {
        id = id_;
        type = 1;
        l = l_;
        r = r_;
        k = k_;
        cnt = 0;
    }
}a[kMaxN], tmp[kMaxN];

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("CRB.in", "r", stdin);
    freopen("CRB.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif

    return 0;
}
