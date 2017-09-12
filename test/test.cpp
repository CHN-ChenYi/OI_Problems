/*
Name: K-th(POJ2104)
Author: godwings
Date: 11/09/2017
*/
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int kMaxM = 5010;
const int kMaxN = 100010;
const int inf = 0x7fffffff;
using std::sort;
using std::lower_bound;

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
    Point() {
        x = id = 0;
    }
    Point(const int x_, const int id_) {
        x = x_;
        id = id_;
    }
    bool operator<(const Point rhs) const {
        return x < rhs.x;
    }
}a[kMaxN];
struct Query {
    int l, r, k;
    int id;
    int cnt;
}q[kMaxM], tmp[kMaxM];
int tr[kMaxN], ans[kMaxM];
inline int lowerbit(const int x) {
    return x & -x;
}
void Calc(const int q_id_l, const int q_id_r, const int ans_l, const int ans_r) {
    const int pos = lower_bound(a + 1, a + n + 1, Point(ans_l, 0)) - a;
    for (int i = pos; i <= n && a[i].x <= ans_r; i++) {
        for (int j = a[i].id; j <= n; j += lowerbit(j))
            tr[j]++;
    }
    for (int i = q_id_l; i <= q_id_r; i++) {
        q[i].cnt = 0;
        for (int j = q[i].r; j; j -= lowerbit(j))
            q[i].cnt += tr[j];
        for (int j = q[i].l - 1; j; j -= lowerbit(j))
            q[i].cnt -= tr[j];
    }
    for (int i = pos; i <= n && a[i].x <= ans_r; i++) {
        for (int j = a[i].id; j <= n; j += lowerbit(j))
            tr[j]--;
    }
}
void OverallDichotomy(const int q_id_l, const int q_id_r, const int ans_l, const int ans_r) {
    if (ans_l == ans_r) {
        for (int i = q_id_l; i <= q_id_r; i++)
            ans[q[i].id] = ans_l;
        return;
    }
    const int ans_mid = (ans_l + ans_r) >> 1;
    Calc(q_id_l, q_id_r, ans_l, ans_mid);
    int left_ptr = q_id_l, right_ptr = q_id_r;
    for (int i = q_id_l; i <= q_id_r; i++) {
        if (q[i].k <= q[i].cnt) {
            tmp[left_ptr++] = q[i];
        } else {
            q[i].k -= q[i].cnt;
            tmp[right_ptr--] = q[i];
        }
    }
    memcpy(q + q_id_l, tmp + q_id_l, (q_id_r - q_id_l + 1) * sizeof(Query));
    if (left_ptr != q_id_l)
        OverallDichotomy(q_id_l, left_ptr - 1, ans_l, ans_mid);
    if (right_ptr != q_id_r)
        OverallDichotomy(right_ptr + 1, q_id_r, ans_mid + 1, ans_r);
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
