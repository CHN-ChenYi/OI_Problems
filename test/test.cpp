/*
Name: laser(LJOJ4523)
Author: godwings
Date: 22/09/2017
*/
#include <cctype>
#include <cstdio>
#include <cstring>
typedef unsigned long long ULL;

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

struct Disjoint_Set {
 private:
    static const int kMaxN = 20;
    int fa[kMaxN];
    int Find(const int x) {
        return fa[x] == x ? x : (fa[x] = Find(fa[x]));
    }

 public:
    Disjoint_Set() {
         memset(fa, -1, sizeof fa);
    }
    int operator[](const int x) {
        return Find(x);
    }
    bool merge(int x, int y) {
        if ((x = Find(x)) == (y = Find(y)))
            return false;
        fa[y] = x;
        return true;
    }
}DS;

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("laser.in", "r", stdin);
    freopen("laser.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif

    return 0;
}
