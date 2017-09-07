/*
Name: three(LJOJNAN)
Author: godwings
Date: 07/09/2017
*/
#include <cmath>
#include <cctype>
#include <cstdio>
#include <algorithm>
const int kMaxLog = 18;
const int kMaxN = 100010;
const int kMaxM = 200010;
using std::min;
using std::swap;

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

int n, m, q;

int ring_u, ring_v, ring_val;

int G[kMaxN], dst[kMaxM], val[kMaxM], nxt[kMaxM], G_tot;
inline void AddEdge(const int u, const int v, const int w) {
    val[++G_tot] = w; dst[G_tot] = v; nxt[G_tot] = G[u]; G[u] = G_tot;
    val[++G_tot] = w; dst[G_tot] = u; nxt[G_tot] = G[v]; G[v] = G_tot;
}

int dis[kMaxN], fa[kMaxN];
int f[kMaxN][kMaxLog], dep[kMaxN];
void dfs(const int now) {
    for (int i = G[now]; i; i = nxt[i]) {
        if (dst[i] == fa[now])
            continue;
        if (!dep[dst[i]]) {
            dis[dst[i]] = dis[now] + val[i];
            dep[dst[i]] = dep[now] + 1;
            f[dst[i]][0] = now;
            fa[dst[i]] = now;
            dfs(dst[i]);
        } else {
            ring_u = now;
            ring_v = dst[i];
            ring_val = val[i];
        }
    }
}
void Init() {
    dep[1] = 1;
    dfs(1);
    for (int j = 1; j < kMaxLog; j++) {
        for (int i = 1; i <= n; i++)
            f[i][j] = f[f[i][j - 1]][j - 1];
    }
}
int LCA(int x, int y) {
    if (dep[x] != dep[y]) {
        if (dep[x] < dep[y])
            swap(x, y);
        int now = log2(dep[x] - dep[y]);
        for (int i = now; i >= 0; i--) {
            if (dep[f[x][i]] >= dep[y])
                x = f[x][i];
        }
    }
    if (x == y)
        return x;
    int now = log2(dep[x] - 1);
    for (int i = now; i >= 0; i--) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}
inline int GetDis(const int u, const int v) {
    const int fa = LCA(u, v);
    return dis[u] + dis[v] - (dis[fa] << 1);
}

int GetTreeAns(int x, int y, int z) {
    int x_y = LCA(x, y), x_z = LCA(x, z);
    if (dep[x_z] < dep[x_y]) {
        return dis[x] + dis[y] + dis[z] - dis[x_y] - (dis[x_z] << 1);
    } else if (dep[x_z] > dep[x_y]) {
        return dis[x] + dis[y] + dis[z] - (dis[x_y] << 1) - dis[x_z];
    } else {
        int y_z = LCA(y, z);
        if (dep[y_z] < dep[x_y])
            return -0x7fffffff;
        else if (dep[y_z] > dep[x_y])
            return dis[x] + dis[y] + dis[z] - (dis[x_y] << 1) - dis[y_z];
        else
            return dis[x] + dis[y] + dis[z] - (dis[x_y] * 3);
    }
}
int GetRingAns(int x, int y, int z) {
    int ans = GetTreeAns(x, y, z);
    ans = min(ans, ring_val + GetDis(x, ring_u) + GetTreeAns(ring_v, y, z));
    ans = min(ans, ring_val + GetDis(x, ring_v) + GetTreeAns(ring_u, y, z));
    ans = min(ans, ring_val + GetDis(y, ring_u) + GetTreeAns(x, ring_v, z));
    ans = min(ans, ring_val + GetDis(y, ring_v) + GetTreeAns(x, ring_u, z));
    ans = min(ans, ring_val + GetDis(z, ring_u) + GetTreeAns(x, y, ring_v));
    ans = min(ans, ring_val + GetDis(z, ring_v) + GetTreeAns(x, y, ring_u));
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("three.in", "r", stdin);
    freopen("three.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(n, m, q);
    for (int i = 1, u, v, w; i <= m; i++) {
        scan(u, v, w);
        AddEdge(u, v, w);
    }
    Init();
    if (n == m) {
        for (int i = 1, x, y, z; i <= q; i++) {
            scan(x, y, z);
            printf("%d\n", GetRingAns(x, y, z));
        }
    } else {
        for (int i = 1, x, y, z; i <= q; i++) {
            scan(x, y, z);
            printf("%d\n", GetTreeAns(x, y, z));
        }
    }
    return 0;
}
