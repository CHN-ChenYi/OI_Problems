/*
Name: matrices(LJOJ4560)
Author: godwings
Date: 15/10/2017
*/
#include <cstdio>

const int kMaxN = 1000;

#include <cctype>
namespace FastIO {
    template <class T>
    inline void scan(T &x) {
        x = 0;
        char c;
        bool positive = 1;
        while (!isdigit(c = getchar())) {
            if (!positive) positive = 1;
            if (c == '-') positive = 0;
        }
        while (isdigit(c)) {
            x = x * 10 + (c & 0xf);
            c = getchar();
        }
        if (!positive)
            x *= -1;
    }
    inline void scan(char &x) {
        while (!isgraph(x = getchar())) { }
    }
    inline void scan(double &x) {
        x = 0;
        char c;
        bool positive = 1;
        while (!isdigit(c = getchar())) {
            if (!positive) positive = 1;
            if (c == '-') positive = 0;
        }
        while (isdigit(c)) {
            x = x * 10 + (c & 0xf);
            c = getchar();
        }
        if (c == '.') {
            double now = 0.1;
            c = getchar();
            while (isdigit(c)) {
                x += now * (c & 0xf);
                now *= 0.1;
                c = getchar();
            }
        }
        if (!positive)
            x *= -1;
    }
    template <class T_1, class T_2>
    inline void scan(T_1 &a, T_2 &b) {
        scan(a); scan(b);
    }
    template <class T_1, class T_2, class T_3>
    inline void scan(T_1 &a, T_2 &b, T_3 &c) {
        scan(a); scan(b); scan(c);
    }
    template <class T_1, class T_2, class T_3, class T_4>
    inline void scan(T_1 &a, T_2 &b, T_3 &c, T_4 &d) {
        scan(a); scan(b); scan(c); scan(d);
    }
}  // namespace FastIO
using FastIO::scan;

inline int gcd(int a, int b) {
    int t;
    while (b) {
        t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int ans;
int n, m;
char input;
int matrix[kMaxN][kMaxN];
int sum_d[kMaxN], sum_u[kMaxN];

int Find(int x) {
    int c = 0, z = 0;
    for (int i = 2; i < m; i += 3) {
        c += matrix[x][i];
        z += matrix[x][i] - matrix[x][i - 1];
    }
    switch (m % 3) {
        case 0:
            return c;
        case 1:
            return c + matrix[x][m] - z;
        default:
            return c + matrix[x][m];
    }
}

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("matrices.in", "r", stdin);
    freopen("matrices.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif  // ONLINE_JUDGE
    scan(n, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scan(input);
            matrix[i][j] = input - '0';
        }
    }
    for (int i = 2; i < n; i += 3)
        sum_u[i + 1] = sum_u[i - 2] + Find(i) - Find(i - 1);
    for (int i = n - 1; i > 1; i -= 3)
        sum_d[i - 1] = sum_d[i + 2] + Find(i) - Find(i + 1);
    switch (n % 3) {
        case 2:
            ans = sum_u[(n + 1) >> 1];
            break;
        case 1:
            ans = Find((n + 1) >> 1) - sum_u[n >> 1] - sum_d[(n + 3) >> 1];
            break;
        default:
            ans = Find((n + 1) >> 1) - sum_d[n >> 1] - sum_u[(n + 3) >> 1];
            break;
    }
    ans = m - ans;
    const int k = gcd(ans, m);
    printf("%d/%d\n", ans / k, m / k);
    return 0;
}
