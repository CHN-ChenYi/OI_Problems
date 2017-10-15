#include<cstdio>
int Ans, n, m, f[1010][1010], h[1010], g[1010];
int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }
int get() { char c = getchar(); while (c<'0' || c>'9') c = getchar(); return c - '0'; }
int find(int x) {
    int c = 0, z = 0;
    for (int i = 2; i<m; i += 3) c += f[x][i], z += f[x][i] - f[x][i - 1];
    if (m % 3 == 0) return c;
    if (m % 3 == 1) return c + f[x][m] - z;
    if (m % 3 == 2) return c + f[x][m];
}
int main() {
    freopen("matrices.in", "r", stdin);
    freopen("matrices.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) f[i][j] = get();
    for (int i = 2; i<n; i += 3) h[i + 1] = h[i - 2] + find(i) - find(i - 1);
    for (int i = n - 1; i>1; i -= 3) g[i - 1] = g[i + 2] + find(i) - find(i + 1);
    if (n % 3 == 2) Ans = h[n + 1 >> 1];
    if (n % 3 == 1) Ans = find(n + 1 >> 1) - h[n >> 1] - g[n + 3 >> 1];
    if (n % 3 == 0) Ans = find(n + 1 >> 1) - g[n >> 1] - h[n + 3 >> 1];
    Ans = m - Ans;
    int d = gcd(Ans, m);
    Ans /= d; m /= d; printf("%d/%d\n", Ans, m);
    return 0;
}
