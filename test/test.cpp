/*
Name: warehouse(LJOJ4514)
Author: godwings
Date: 15/09/2017
*/
#include <cctype>
#include <cstdio>
const int kMaxN = 100010;
const int kMaxM = 200010;

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

int G[kMaxN], val[kMaxM], dst[kMaxM], nxt[kMaxM], G_tot;
void AddEdge(const int u, const int v, const int w) {
    val[++G_tot] = w; dst[G_tot] = v; nxt[G_tot] = G[u]; G[u] = G_tot;
    val[++G_tot] = w; dst[G_tot] = u; nxt[G_tot] = G[v]; G[v] = G_tot;
}

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("warehouse.in", "r", stdin);
    freopen("warehouse.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(n, m);
    for (int i = 1, u, v, w; i < n; i++) {
        scan(u, v, w);
        AddEdge(u, v, w);
    }

    return 0;
}
