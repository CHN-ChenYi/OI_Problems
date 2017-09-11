/*
Name: K-th(POJ2104)
Author: godwings
Date: 11/09/2017
*/
#include <cctype>
#include <cstdio>
#include <algorithm>
const int kMaxM = 5010;
const int kMaxN = 100010;
const int inf = 0x7fffffff;
using std::sort;

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
struct Point {
    int x, id;
    bool operator<(const Point rhs) const {
        return x < rhs.x;
    }
}a[kMaxN];
struct Query {
    int l, r, k;
    int id;
    int cnt;
}q[kMaxM];
int sum[kMaxN], ans[kMaxM];
void Calc(const int q_id_l, const int q_id_r, const int ans_l, const int ans_r) {

}
void OverallDichotomy(const int q_id_l, const int q_id_r, const int ans_l, const int ans_r) {

}

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("K-th.in", "r", stdin);
    freopen("K-th.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(n, m);
    for (int i = 1; i <= n; i++) {
        scan(a[i].x);
        a[i].id = i;
    }
    n++;
    a[n].id = n;
    a[n].x = inf;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= m; i++) {
        scan(q[i].l, q[i].r, q[i].k);
        q[i].id = i;
    }
    OverallDichotomy(1, m, -inf, inf);
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
    return 0;
}
