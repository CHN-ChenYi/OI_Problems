/*
Name: mod(LJOJ4491)
Author: godwings
Date: 07/09/2017
*/
#include <cctype>
#include <cstdio>
#include <cstring>
const int kMaxN = 310;
const int kMaxM = 110;
const int kMaxA = 2000;

namespace FastIO {
    template <class T>
    inline void scan(T &x) {
        bool positive = 1;
        char c;
        while (isdigit(c = getchar()) == 0) {
            if (!positive) positive = 1;
            if (c == '-') positive = 0;
        }
        x = 0;
        for (; isdigit(c) != 0; c = getchar())
            x = x * 10 + (c & 0xf);
        if (!positive)
            x *= -1;
    }
    template <class T>
    inline void scan(T &x, T &y) {
        scan(x); scan(y);
    }
    template <class T>
    inline void scan(T &x, T &y, T &z) {
        scan(x); scan(y); scan(z);
    }
}  // namespace FastIO
using FastIO::scan;

int Prim[kMaxN], P_tot;
bool prim_[kMaxA];
void Init() {
    Prim[0] = 1;
    for (int i = 2; i <= kMaxA; i++) {
        if (prim_[i] == 0)
            Prim[++P_tot] = i;
        for (int j = 1; j <= P_tot; j++) {
            if (i * Prim[j] > kMaxA)
                break;
            prim_[i * Prim[j]] = 1;
            if (i % Prim[j] == 0)
                break;
        }
    }
}

int n, m;
int a[kMaxN], b[kMaxN];

bool flag = true;
struct Data {
    int remainder[kMaxN], ans[kMaxM];
    Data() {
        memset(remainder, 0, sizeof remainder);
        memset(ans, 0, sizeof ans);
    }
    explicit Data(int x) {
        for (int i = 0; i <= n; i++)
            remainder[i] = x % Prim[i];
        for (int i = 1; i <= m; i++)
            ans[i] = x % b[i];
    }
    Data operator+=(const Data rhs) {
        for (int i = 0; i <= n; i++)
            remainder[i] = (remainder[i] + rhs.remainder[i]) % Prim[i];
        for (int i = 1; i <= m; i++)
            ans[i] = (ans[i] + rhs.ans[i]) % b[i];
        return *this;
    }
    Data operator*=(const Data rhs) {
        for (int i = 0; i <= n; i++)
            remainder[i] = 1ll * remainder[i] * rhs.remainder[i] % Prim[i];
        for (int i = 1; i <= m; i++)
            ans[i] = 1ll * ans[i] * rhs.ans[i] % b[i];
        return *this;
    }
};

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("mod.in", "r", stdin);
    freopen("mod.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    Init();
    scan(n, m);
    for (int i = 1; i <= n; i++)
        scan(a[i]);
    for (int i = 1; i <= m; i++)
        scan(b[i]);
    Data ans = Data(1), prod = Data(1);
    for (int i = 1; i <= n; i++) {
        while (ans.remainder[i] != a[i]) {
            ans += prod;
            flag = false;
        }
        prod *= Data(Prim[i]);
    }
    if (flag)
        ans = prod;
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans.ans[i]);
    return 0;
}
