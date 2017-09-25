#include<cstdio>
const int N = 5005, mod = 1e9 + 7, a[3] = {2,1,-1};
int n, k, f[N][N][2];
int main() {
    freopen("val.in", "r", stdin);
    freopen("val.out", "w", stdout);
    scanf("%d%d", &n, &k);
    f[0][0][1] = 1;
    for (int i = 1; i <= k; i++)f[0][i][0] = 1;
    for (int i = 0; i<n; i++)
        for (int j = 0; j <= k; j++)
            for (int t = 0; t<2; t++)if (f[i][j][t])
                for (int p = 0; p<3; p++) {
                    int q = j - a[p], x = t; if (q<0)continue;
                    if (!q)x = 1;
                    if (q <= k)f[i + 1][q][x] = (f[i + 1][q][x] + f[i][j][t]) % mod;
                }
    int ans = 0;
    for (int i = 0; i <= k; i++)ans = (ans + f[n][i][1]) % mod;
    printf("%d\n", ans);
    return 0;
}
