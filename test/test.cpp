/*
Name: laser(LJOJ4523)
Author: godwings
Date: 22/09/2017
*/
#include <cctype>
#include <cstdio>
#include <vector>
#include <cstring>
typedef unsigned long long ULL;
using std::vector;

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

struct Disjoint_Set {
 private:
    static const int kMaxN = 20;
    int fa[kMaxN];
    int Find(const int x) {
        return fa[x] == x ? x : (fa[x] = Find(fa[x]));
    }

 public:
    Disjoint_Set() {
         memset(fa, -1, sizeof fa);
    }
    int operator[](const int x) {
        return Find(x);
    }
    bool merge(int x, int y) {
        if ((x = Find(x)) == (y = Find(y)))
            return false;
        fa[y] = x;
        return true;
    }
}DS;

int n, k;
ULL base[20];

struct Segment {
    int l, r;
    Segment(const int l_, const int r_) {
        l = l_;
        r = r_;
    }
};
vector<Segment> seg;

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("laser.in", "r", stdin);
    freopen("laser.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(n, k);
    base[0] = 1;
    for (int i = 1; i <= k; i++)
        base[i] = base[i] * 10;
    // seg.push_back(Segment(0, (1ULL << 64) - 1));
    for (int i = 1; i <= n; i++) {
        ULL l, r;
        scan(l, r);
        if (seg.empty() || seg.back().r + 1 != l)
            seg.push_back(Segment(l, r));
        else
            seg.back().r = r;
    }
    n = seg.size();

    return 0;
}
