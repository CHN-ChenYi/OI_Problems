/*
Name: delta(LJOJ4508)
Author: godwings
Date: 10/09/2017
*/
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int kMaxN = 1010;
const int kMaxTop = 1000;
using std::swap;

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
    inline void scan(T &a, T &b, T &c, T &d) {
        scan(a); scan(b); scan(c); scan(d);
    }
}  // namespace FastIO
using FastIO::scan;

int n, m;
long long ans;
struct Modify {
    int x, y, z;
    Modify() {
        x = y = z = 0;
    }
    Modify(const int x_, const int y_, const int z_) {
        x = x_;
        y = y_;
        z = z_;
    }
}stack[kMaxN]; int top;

int sum[kMaxN][kMaxN], del[kMaxN][kMaxN];
void ReBuild() {
    memset(del, 0, sizeof del);
    for (int i = 0; i < top; i++) {
        const int x = stack[i].x, y = stack[i].y, z = stack[i].z;
        for (int j = 1; j <= z; j++) {
            del[x + j - 1][y]++;
            del[x + j - 1][y + j]--;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++)
            del[i][j] += del[i][j - 1];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            del[i][j] += del[i][j - 1];
            sum[i][j] += del[i][j];
        }
    }
    top = 0;
}
int Calc(int x, int y, int z, int a, int b, int c) {
    if (y > b) {
        swap(x, a);
        swap(y, b);
        swap(z, c);
    }
    int inter = x + (b - y), len;
    if (inter > x + z - 1)
        return 0;
    if (a + c - 1 > x + z - 1) {
        if (a > x + z - 1)
            return 0;
        if (a <= x + z - 1 && a >= inter)
            len = x + z - 1 - a + 1;
        else
            len = x + z - 1 - inter + 1;
        return len * (len + 1) >> 1;
    }
    if (a + c - 1 <= x + z - 1 && a + c - 1 >= inter) {
        if (a >= inter)
            len = c;
        else 
            len = a + c - 1 - inter + 1;
        return
            len * (len + 1) >> 1;
    }
    return 0;
}

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("delta.in", "r", stdin);
    freopen("delta.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(n, m);
    for (int i = 1, op, x, y, z; i <= m; i++) {
        scan(op, x, y, z);
        if (op == 1) {
            stack[top++] = Modify(x, y, z);
            if (top >= kMaxTop)
                ReBuild();
        } else {
            ans = 0;
            for (int i = 1; i <= z; i++)
                ans += sum[x + i - 1][y + i - 1] - sum[x + i - 1][y - 1];
            for (int i = 0; i < top; i++)
                ans += Calc(stack[i].x, stack[i].y, stack[i].z, x, y, z);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
