//
//  main.cpp
//  string
//
//  Created by apple on 2017/9/9.
//  Copyright © 2017年 stn. All rights reserved.
//

#include <cstdio>
int n, a, b, c, d, l, r;
int dif[200000], summ[200000][30], q[200000], pre[200000];
char s[200000];
long long f[200000], sum[200000];
inline int min(const int a, const int b) { return a<b ? a : b; }
inline long long min(const long long a, const long long b) { return a<b ? a : b; }
inline bool check(int x, int y) {
    int t = 0;
    for (int i = 0; i<26; i++)
        if (summ[y][i] - summ[x - 1][i]>t) t = summ[y][i] - summ[x - 1][i];
    return t >= l && t <= r;
}
inline void doo(int x, int y) {
    if (y<x && y >= 0) f[x] = min(f[x], f[y] + b + (long long)a*(sum[x] - sum[y])*(sum[x] - sum[y]));
}
inline long long get(int x, int y) { return f[x - 1] + (long long)c*(sum[y] - sum[x - 1]) + d; }
const long long INF = 2305843009213693952ll;
int main() {
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    scanf("%d%d%d%d%d%d%d", &n, &a, &b, &c, &d, &l, &r);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &dif[i]);
        s[i] -= 'a';
        sum[i] = sum[i - 1] + dif[i];
        f[i] = INF;
    }
    for (int i = 1; i <= n; i++) {
        summ[i][(int)s[i]]++;
        for (int j = 0; j<26; j++) summ[i][j] += summ[i - 1][j];
    }
    for (int i = n, j; i >= 1; i--)if (dif[i]) {
        for (j = 1; !dif[i + j] && i + j <= n; j++) pre[i + j] = i;
        if (i + j <= n) pre[i + j] = i;
    }
    int he = 1, st = 0, R = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1, k = i; j <= 80 && k>0; j++, k = pre[k]) {
            for (int T = -2; T <= 2; T++) doo(i, k + T);
        }
        while (he <= st && !check(q[he], i)) he++;
        while (R <= i && check(R, i)) {
            while (he <= st && get(R, i) <= get(q[st], i)) st--;
            q[++st] = R++;
        }
        if (he <= st)f[i] = min(f[i], get(q[he], i));
        doo(i, 0);
        printf("%lld\n", f[i]);
    }
    return 0;
}
