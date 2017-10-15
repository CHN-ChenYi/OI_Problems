#include <cstdio>
#define N 1000
int mat[N][N], s_u[N][N], s_d[N][N];
inline int gcd(int a, int b) {
    for (;;) {
        if (a == 0)
            return b;
        b %= a;
        if (b == 0)
            return a;
        a %= b;
    }
}
int main() {
    freopen("matrices.in", "r", stdin);
    freopen("matrices.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        char c;
        while ((c = getchar()) >> 4 != 3);
        mat[i][0] = c - '0';
        for (int j = 1; j < m; ++j)
            mat[i][j] = getchar() - '0';
    }
    s_u[0][0] = mat[0][0];
    for (int j = 2; j < m; ++j)
        switch (j % 3) {
            case 0:
                s_u[0][j] = mat[0][j] - s_u[0][j - 1];
                break;
            case 2:
                s_u[0][j] = mat[0][j - 1] - s_u[0][j - 2];
                break;
        }
    for (int i = 2; i < n; ++i) {
        int last_mat, last_s;
        switch (i % 3) {
            case 0:
                last_mat = i;
                last_s = i - 1;
                break;
            case 1:
                continue;
            default:
                last_mat = i - 1;
                last_s = i - 2;
        }
        s_u[i][0] = mat[last_mat][0] - s_u[last_s][0];
        for (int j = 2; j < m; ++j)
            switch (j % 3) {
                case 0:
                    s_u[i][j] = mat[last_mat][j] - s_u[last_s][j]
                        - s_u[last_s][j - 1] - s_u[i][j - 1];
                    break;
                case 2:
                    s_u[i][j] = mat[last_mat][j] - s_u[last_s][j]
                        - s_u[last_s][j - 2] - s_u[i][j - 2];
                    break;
            }
    }
    s_d[n - 2][0] = mat[n - 1][0];
    for (int j = 2; j < m; ++j)
        switch (j % 3) {
            case 0:
                s_d[n - 2][j] = mat[n - 1][j] - s_d[n - 2][j - 1];
                break;
            case 2:
                s_d[n - 2][j] = mat[n - 1][j - 1] - s_d[n - 2][j - 2];
                break;
        }
    for (int i = n - 3; i >= 0; --i) {
        int last_mat = i + 1, last_s;
        switch ((n - i) % 3) {
            case 0:
                last_s = i + 1;
                break;
            case 1:
                continue;
            default:
                last_s = i + 2;
        }
        s_d[i][0] = mat[last_mat][0] - s_d[last_s][0];
        for (int j = 2; j < m; ++j)
            switch (j % 3) {
                case 0:
                    s_d[i][j] = mat[last_mat][j] - s_d[last_s][j]
                        - s_d[last_s][j - 1] - s_d[i][j - 1];
                    break;
                case 2:
                    s_d[i][j] = mat[last_mat][j] - s_d[last_s][j]
                        - s_d[last_s][j - 2] - s_d[i][j - 2];
                    break;
            }
    }
    int ans = 0;
    const int tmp_n = n >> 1;
    switch (n % 6) {
        case 1:
            for (int j = 0; j < m; ++j)
                if (j % 3 != 1)
                    ans += s_u[tmp_n][j] - s_d[tmp_n + 1][j];
            break;
        case 3:
            for (int j = 0; j < m; ++j)
                if (j % 3 != 1)
                    ans += s_u[tmp_n - 1][j] - s_d[tmp_n - 1][j];
            break;
        case 5:
            for (int j = 0; j < m; ++j)
                if (j % 3 != 1)
                    ans += s_u[tmp_n][j];
    }
    int g = gcd(m, ans);
    printf("%d/%d\n", (m - ans) / g, m / g);
    return 0;
}
