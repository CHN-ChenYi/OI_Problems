/*
Name: fun(LJOJ4532)
Author: godwings
Date: 26/09/2017
*/
#pragma GCC optimize(3)
#include <cctype>
#include <cstdio>
#include <algorithm>
#define kMaxN 60010
#define kMod 1000000007
using std::min;
using std::max;

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

template <class T>
inline T Inv(T x) {
    T ret = 1;
    int n = kMod - 2;
    while (n) {
        if (n & 1)
            ret *= x;
        x *= x;
        n >>= 1;
    }
    return ret;
}

struct Int {
 private:
    int num;

 public:
    Int() {
        num = 0;
    }
    Int(const int x) {
        num = x;
    }
    inline Int operator=(const int &rhs) {
        num = (num + rhs) % kMod;
        return *this;
    }
    inline Int operator+(const int &rhs) {
        return Int((num + rhs) % kMod);
    }
    inline Int operator+(const Int &rhs) {
        return Int((num + rhs.num) % kMod);
    }
    inline void operator+=(const Int &rhs) {
        num = (num + rhs.num) % kMod;
    }
    inline Int operator-(const Int &rhs) {
        return Int(((num - rhs.num) % kMod + kMod) % kMod);
    }
    inline Int operator*(const int &rhs) {
        return Int(1ll * num * rhs % kMod);
    }
    inline Int operator*(const Int &rhs) {
        return Int(1ll * num * rhs.num % kMod);
    }
    inline void operator*=(const Int &rhs) {
        num = 1ll * num * rhs.num % kMod;
    }
    void Print_endl() {
        printf("%d\n", num);
    }
};

int n, k;
Int fac[kMaxN], inv_fac[kMaxN];
Int f[kMaxN >> 1][20];
Int ans, all;

inline Int C(int n, int m) {
    return fac[n] * inv_fac[m] * inv_fac[n - m];
}

void Init() {
    fac[0] = inv_fac[0] = 1;
    const int lim = max(n, k);
    for (int i = 1; i <= lim; i++) {
        fac[i] = fac[i - 1] * i;
        inv_fac[i] = Inv(fac[i]);
    }
}

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("fun.in", "r", stdin);
    freopen("fun.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(n, k);
    Init();
    f[0][0] = 1;
    for (int i = 1; i <= (n >> 1); i++) {
        for (int j = 1; j <= min(k, 15); j++) {
            int x = i;
            while (x) {
                f[i][j] += f[i ^ x][j - 1] * inv_fac[x << 1];
                x = (x - 1) & i;
            }
            ans += f[i][j] * fac[i << 1] * C(k, j);
        }
    }
    while (n--)
        all = (all + 1) * k;
    ans = all - ans;
    ans.Print_endl();
    return 0;
}
