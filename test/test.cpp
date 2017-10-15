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
int sum_u[kMaxN][kMaxN], sum_d[kMaxN][kMaxN];

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
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scan(input);
            matrix[i][j] = input - '0';
        }
    }
    sum_u[0][0] = matrix[0][0];
    for (int j = 2; j < m; j++) {
        if (j % 3 == 0)
            sum_u[0][j] = matrix[0][j] - sum_u[0][j - 1];
        else if (j % 3 == 2)
            sum_u[0][j] = matrix[0][j - 1] - sum_u[0][j - 2];
    }
    for (int i = 2; i < n; i++) {
        int last_mat, last_sum;
        switch (i % 3) {
            case 0:
                last_mat = i;
                last_sum = i - 1;
                break;
            case 1:
                continue;
            default:
                last_mat = i - 1;
                last_sum = i - 2;
        }
        sum_u[i][0] = matrix[last_mat][0] - sum_u[last_sum][0];
        for (int j = 2; j < m; j++) {
            if (j % 3 == 0)
                sum_u[i][j] = matrix[last_mat][j] - sum_u[last_sum][j] - sum_u[last_sum][j - 1] - sum_u[i][j - 1];
            else
                sum_u[i][j] = matrix[last_mat][j] - sum_u[last_sum][j] - sum_u[last_sum][j - 2] - sum_u[i][j - 2];
        }
    }
    sum_d[n - 2][0] = matrix[n - 1][0];
    for (int j = 2; j < m; j++) {
        if (j % 3 == 0)
            sum_d[n - 2][j] = matrix[n - 1][j] - sum_d[n - 2][j - 1];
        else if (j % 3 == 2)
            sum_d[n - 2][j] = matrix[n - 1][j - 1] - sum_d[n - 2][j - 2];
    }
    for (int i = n - 3; i >= 0; i--) {
        int last_matrix = i + 1, last_sum;
        switch ((n - i) % 3) {
            case 0:
                last_sum = i + 1;
                break;
            case 1:
                continue;
            default:
                last_sum = i + 2;
        }
        sum_d[i][0] = matrix[last_matrix][0] - sum_d[last_sum][0];
        for (int j = 2; j < m; j++) {
            if (j % 3 == 0)
                sum_d[i][j] = matrix[last_matrix][j] - sum_d[last_sum][j] - sum_d[last_sum][j - 1] - sum_d[i][j - 1];
            else if (j % 3 == 2)
                sum_d[i][j] = matrix[last_matrix][j] - sum_d[last_sum][j] - sum_d[last_sum][j - 2] - sum_d[i][j - 2];
        }
    }
    const int o = n >> 1;
    switch (n % 6) {
        case 1:
            for (int j = 0; j < m; ++j) {
                if (j % 3 != 1)
                    ans += sum_u[o][j] - sum_d[o + 1][j];
            }
            break;
        case 3:
            for (int j = 0; j < m; ++j) {
                if (j % 3 != 1)
                    ans += sum_u[o - 1][j] - sum_d[o - 1][j];
            }
            break;
        case 5:
            for (int j = 0; j < m; ++j) {
                if (j % 3 != 1)
                    ans += sum_u[o][j];
            }
    }
    const int k = gcd(m, ans);
    printf("%d/%d\n", (m - ans) / k, m / k);
    return 0;
}
