#include<bits/stdc++.h>
#define double long double
using namespace std;
double p[55][55][2555], ev[55][55][2555];
int main() {
    freopen("fighting.in", "r", stdin);
    freopen("fighting.out", "w", stdout);
    int n, m;
    double r, pstart = 0, pend = 0, evstart = 0, evend = 0;
    scanf("%d%d%Lf", &n, &m, &r);
    p[0][0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= i * j; k++) {  // if (p[i][j][k]>1e-20)
                if ((i == n) && (j == m)) {
                    pend += p[i][j][k]; evend += ev[i][j][k];
                    continue;
                }
                double all = n * m, x, thsp = p[i][j][k], thsev = ev[i][j][k];

                //do nothing
                x = k / all * (1 - r);
                thsev += 1 / (1 - x) * thsp;
                all -= k * (1 - r);

                //be sad
                x = k / all * r;
                pstart += x * thsp;
                evstart += x * (thsev - thsp);

                //new green
                x = (n - i)*j / all;
                p[i + 1][j][k + 1] += x * thsp;
                ev[i + 1][j][k + 1] += x * thsev;

                //new red
                x = i * (m - j) / all;
                p[i][j + 1][k + 1] += x * thsp;
                ev[i][j + 1][k + 1] += x * thsev;

                //new both
                x = (n - i) * (m - j) / all;
                p[i + 1][j + 1][k + 1] += x * thsp;
                ev[i + 1][j + 1][k + 1] += x * thsev;

                //new neither
                x = (i * j - k) / all;
                p[i][j][k + 1] += x * thsp;
                ev[i][j][k + 1] += x * thsev;
            }
        }
    }
    printf("%.6Lf\n", evend / pend + evstart / pend);
}
