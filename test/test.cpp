/*
Name: val(LJOJ4529)
Author: godwings
Date: 25/09/2017
*/
#include <cctype>
#include <cstdio>
const int kMaxN = 5010;
const int kMod = 1e9 + 7;
const int step[3] = {1, 2, -1};

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

int n, m;
struct Int {
    int num;
    bool operator!() const {
        return num == 0;
    }
    Int operator=(const int &rhs) {
        num += rhs;
        num %= kMod;
        return *this;
    }
    void operator+=(const Int &rhs) {
        num += rhs.num;
        num %= kMod;
    }
    void Print_endl() {
        printf("%d\n", num);
    }
}f[kMaxN][kMaxN][2], ans;

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("val.in", "r", stdin);
    freopen("val.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(n, m);
    f[0][0][1] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k < 2; k++) {
                if (!f[i][j][k])
                    continue;
                for (int s = 0; s < 3; s++) {
                    int nxt_j = j - step[s], x = k;
                    if (nxt_j < 0)
                        continue;
                    if (!nxt_j)
                        x = 1;
                    if (nxt_j <= k)
                        f[i + 1][nxt_j][x] += f[i][j][k];
                }
            }
        }
    }
    for (int i = 0; i <= m; i++)
        ans += f[n][i][1];
    ans.Print_endl();
    return 0;
}
