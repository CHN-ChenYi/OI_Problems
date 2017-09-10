//
//  main.cpp
//  delta
//
//  Created by apple on 2017/9/9.
//  Copyright © 2017年 stn. All rights reserved.
//

#include <cstdio>
#include <cstring>
int n, m, top, a[1010][1010], b[1010][1010];
struct S { int x, y, z; }stk[1010];
inline void swp(int&a, int&b) { int t = a; a = b; b = t; }
inline void rebuild() {
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= top; i++) {
        int x = stk[i].x, y = stk[i].y, z = stk[i].z;
        for (int j = 1; j <= z; j++)b[x + j - 1][y]++, b[x + j - 1][y + j]--;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)b[i][j] += b[i][j - 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)b[i][j] += b[i][j - 1], a[i][j] += b[i][j];
    top = 0;
}
inline int calc(int x, int y, int z, int a, int b, int c) {
    if (y>b)swp(x, a), swp(y, b), swp(z, c);
    int t = x + (b - y), r; if (t>x + z - 1)return 0;
    if (a + c - 1>x + z - 1) {
        if (a>x + z - 1)return 0;
        if (a <= x + z - 1 && a >= t)r = x + z - 1 - a + 1;
        else r = x + z - 1 - t + 1;
        return r*(r + 1) / 2;
    }
    if (a + c - 1 <= x + z - 1 && a + c - 1 >= t) {
        if (a >= t)r = c;
        else r = a + c - 1 - t + 1;
        return r*(r + 1) / 2;
    }
    return 0;
}
int main() {
    freopen("delta.in", "r", stdin);
    freopen("delta.out", "w", stdout);
    scanf("%d%d", &n, &m);
    while (m--) {
        int t, x, y, z;
        scanf("%d%d%d%d", &t, &x, &y, &z);
        if (t == 1) {
            stk[++top] = (S) { x, y, z };
            if (top>700)rebuild();
        }
        if (t == 2) {
            long long tmp = 0;
            for (int i = 1; i <= z; i++)tmp += a[x + i - 1][y + i - 1] - a[x + i - 1][y - 1];
            for (int i = 1; i <= top; i++)tmp += calc(stk[i].x, stk[i].y, stk[i].z, x, y, z);
            printf("%lld\n", tmp);
        }
    }
    return 0;
}
