/*
Name: Jam(HDU5618)
Author: godwings
Date: 27/09/2017
*/
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int kMaxN = 1e5 + 10;
using std::max;
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

struct BIT {
private:
    static const int MAXN = 1e5 + 10;
    int n, tr[MAXN];
    inline int lowbit(const int x) {
        return x & -x;
    }
public:
    void Init(const int n_) {
        n = n_;
    }
    void Modify(int pos, int del) {
        while (pos < n) {
            tr[pos] += del;
            pos += lowbit(pos);
        }
    }
    int Query(int pos) {
        int ret = 0;
        while (pos) {
            ret += tr[pos];
            pos -= lowbit(pos);
        }
        return ret;
    }
}tree;

int T, n;
int max_z;
int ans[kMaxN];

struct Point {
    int x, y, z, id;
    bool operator==(const Point &rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    bool operator<(const Point &rhs) const {
        if (x != rhs.x)
            return x < rhs.x;
        return y != rhs.y ? y < rhs.y : z < rhs.z;
    }
}a[kMaxN], tmp[kMaxN];

void CDQ(const int l, const int r) {
    if (l == r)
        return;
    const int m = (l + r) >> 1;
    CDQ(l, m); CDQ(m + 1, r);
    for (int i = l, left_ptr = l, right_ptr = m + 1; i <= r; i++) {
        if (left_ptr <= m && (right_ptr > r || a[left_ptr].y < a[right_ptr].y)) {
            tree.Modify(a[left_ptr].z, 1);
            tmp[i] = a[left_ptr++];
        } else {
            ans[a[right_ptr].id] += tree.Query(a[right_ptr].z);
            tmp[i] = a[right_ptr++];
        }
    }
    for (int i = l; i <= m; i++)
        tree.Modify(a[i].z, -1);
    memcpy(a + l, tmp + l, (r - l + 1) * sizeof(Point));
}

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("Jam.in", "r", stdin);
    freopen("Jam.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(T);
    while (T--) {
        scan(n);
        max_z = 0;
        for (int i = 1; i <= n; i++) {
            scan(a[i].x, a[i].y, a[i].z);
            max_z = max(max_z, a[i].z);
            a[i].id = i;
        }
        tree.Init(max_z);
        sort(a + 1, a + 1 + n);
        for (int i = n - 1; i; i--) {
            if (a[i] == a[i + 1])
                ans[a[i].id] = ans[a[i + 1].id] + 1;
        }
        CDQ(1, n);
        for (int i = 1; i <= n; i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}
