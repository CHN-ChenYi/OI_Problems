/*
Name: Jam(HDU5618)
Author: godwings
Date: 27/09/2017
*/
#include <cctype>
#include <cstdio>
const int kMaxN = 1e5 + 10;

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

struct BIT {
private:
    static const int MAXN = 1e5 + 10;
    int n, tr[MAXN];
    inline int lowbit(const int x) {
        return x & -x;
    }
public:
    void Init(const int n_) {
        n = n_;
    }
    void Modify(int pos, int del) {
        while (pos < n) {
            tr[pos] += del;
            pos += lowbit(pos);
        }
    }
    int Query(int pos) {
        int ret = 0;
        while (pos) {
            ret += tr[pos];
            pos -= lowbit(pos);
        }
        return ret;
    }
};

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("Jam.in", "r", stdin);
    freopen("Jam.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif

    return 0;
}
