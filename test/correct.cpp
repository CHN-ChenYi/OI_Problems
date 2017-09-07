#include <cstdio>
#include <cstring>
typedef long long LL;

inline bool prime(int x) {
    for (int i = 2; i * i <= x; i++) if (x % i == 0) return false;
    return true;
}

int p[508], pn = 0, a[508], n, b[108], m;

struct num {
    int mp[508], mb[108];
    inline num() {
        memset(mp, 0, sizeof(mp));
        memset(mb, 0, sizeof(mb));
    }
    inline num(int x) {
        for (int i = 0; i <= n; i++)
            mp[i] = x % p[i];
        for (int i = 1; i <= m; i++)
            mb[i] = x % b[i];
    }
    inline num &operator +=(const num &other) {
        for (int i = 0; i <= n; i++)
            mp[i] = (mp[i] + other.mp[i]) % p[i];
        for (int i = 1; i <= m; i++)
            mb[i] = (mb[i] + other.mb[i]) % b[i];
    }
    inline num &operator *=(const num &other) {
        for (int i = 0; i <= n; i++)
            mp[i] = mp[i] * other.mp[i] % p[i];
        for (int i = 1; i <= m; i++)
            mb[i] = (LL)mb[i] * other.mb[i] % b[i];
    }
};


int main() {
    freopen("mod.in", "r", stdin);
    freopen("mod.out", "w", stdout);
    scanf("%d%d", &n, &m);
    p[0] = 1; a[0] = 0;
    for (int i = 2;; i++) if (prime(i)) {
        p[++pn] = i;
        if (pn >= n) break;
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= m; i++)
        scanf("%d", b + i);
    num ans, prod = 1;
    bool zero = true;
    for (int i = 1; i <= n; i++) {
        while (ans.mp[i] != a[i]) {
            ans += prod;
            zero = false;
        }
        prod *= p[i];
    }
    if (zero) ans = prod;
    for(int i = 1; i <= m; i++)
        printf("%d\n", ans.mb[i]);
    return 0;
}
