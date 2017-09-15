/*
Name: warehouse(LJOJ4514)
Author: godwings
Date: 15/09/2017
*/
#include <cctype>
#include <cstdio>
const int kMaxN = 100010;
const int kMaxM = 200010;
typedef long long LL;

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

int f[kMaxN][16], g[kMaxN], t[16];
void DFS_1(int x, int fa) {
    for (int i = G[x]; i; i = nxt[i]) {
        if (dst[i] == fa)
            continue;
        DFS_1(dst[i], x);
        g[x] += g[dst[i]] + (val[i] >> 4);
        f[x][val[i] & 0xf]++;
        for (int j = 0; j < 16; j++) {
            int k = j + val[i];
            g[x] += (k >> 4) * f[dst[i]][j];
            f[x][k % 16] += f[dst[i]][j];
        }
    }
}
void DFS_2(int x, int fa) {
    for (int i = G[x]; i; i = nxt[i]) {
        if (dst[i] == fa)
            continue;
        int tmp = g[x] - g[dst[i]];
        for (int j = 0; j < 16; j++) {
            int k = j + val[i];
            tmp -= (k >> 4) * f[dst[i]][j];
            t[k & 0xf] = f[x][k & 0xf] - f[dst[i]][j];
        }
        t[val[i] & 0xf]--;
        g[dst[i]] += tmp;
        f[dst[i]][val[i] % 16]++;
        for (int j = 0; j < 16; j++) {
            int k = j + val[i];
            g[dst[i]] += (k >> 4) * t[j];
            f[dst[i]][k & 0xf] += t[j];
        }
        DFS_2(dst[i], x);
    }
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
    DFS_1(1, 0);
    DFS_2(1, 0);
    for (int i = 1; i <= n; i++) {
        LL ans = g[i] * 16;
        for (int j = 0; j < 16; j++)
            ans += (j ^ m) * f[i][j];
        printf("%lld\n", ans);
    }
    return 0;
}
