#include <bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define per(i,r,l) for(int i=r;i>=l;i--)
#define mo 1000000007
#define N 60005
int inv(int x) {
    int y = mo - 2, s = 1;
    while (y) {
        if (y & 1)
            s = 1ll * s * x % mo;
        y >>= 1;
        x = 1ll * x * x % mo;
    }
    return s;
}
int n, k, fac[N], ifac[N];
int dp[N / 2][16], ans;
int main() {
    char fni[] = "fun.in", fno[] = "fun.out";
    freopen(fni, "r", stdin);
    freopen(fno, "w", stdout);
    scanf("%d%d", &n, &k);
    fac[0] = ifac[0] = 1;
    rep(i, 1, std::max(n, k))
        ifac[i] = inv(fac[i] = 1ll * fac[i - 1] * i % mo);
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    ans = 0;
    rep(i, 1, n / 2) {
        rep(j, 1, std::min(k, 15)) {
            int x = i;
            while (x) {
                dp[i][j] = (dp[i][j] + 1ll * ifac[x * 2] * dp[i ^ x][j - 1]) % mo;
                x = (x - 1) & i;
            }
            ans = (ans + 1ll * dp[i][j] * fac[i * 2] % mo * fac[k] % mo * ifac[j] % mo * ifac[k - j]) % mo;
        }
    }
    int all = 0;
    while (n--)
        all = 1ll * (all + 1) * k % mo;
    printf("%d\n", (all - ans + mo) % mo);
    fclose(stdin);
    fclose(stdout);
}
