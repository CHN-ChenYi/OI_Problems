/*
Name: strings(LJOJ4561)
Author: godwings
Date: 15/10/2017
*/
#include <set>
#include <cstdio>
#include <cstring>
using std::set;

typedef long long LL;
const int kMaxN = 1e5 + 10;
const int kMaxM = kMaxN << 2;

#include <cctype>
namespace FastIO {
    template <class T>
    inline void scan(T &x) {
        x = 0;
        char c;
        bool positive = 1;
        while (!isdigit(c = getchar())) {
            if (!positive) positive = 1;
            if (c == '-') positive = 0;
        }
        while (isdigit(c)) {
            x = x * 10 + (c & 0xf);
            c = getchar();
        }
        if (!positive)
            x *= -1;
    }
    inline void scan(char &x) {
        while (!isgraph(x = getchar())) { }
    }
    inline void scan(double &x) {
        x = 0;
        char c;
        bool positive = 1;
        while (!isdigit(c = getchar())) {
            if (!positive) positive = 1;
            if (c == '-') positive = 0;
        }
        while (isdigit(c)) {
            x = x * 10 + (c & 0xf);
            c = getchar();
        }
        if (c == '.') {
            double now = 0.1;
            c = getchar();
            while (isdigit(c)) {
                x += now * (c & 0xf);
                now *= 0.1;
                c = getchar();
            }
        }
        if (!positive)
            x *= -1;
    }
    template <class T_1, class T_2>
    inline void scan(T_1 &a, T_2 &b) {
        scan(a); scan(b);
    }
    template <class T_1, class T_2, class T_3>
    inline void scan(T_1 &a, T_2 &b, T_3 &c) {
        scan(a); scan(b); scan(c);
    }
    template <class T_1, class T_2, class T_3, class T_4>
    inline void scan(T_1 &a, T_2 &b, T_3 &c, T_4 &d) {
        scan(a); scan(b); scan(c); scan(d);
    }
}  // namespace FastIO
using FastIO::scan;

int n, m;
set<int> s;

struct Operation {
    int idx; // 0->Modify
    int x, y; // x->i, y->pre[i]
    int val;
    Operation() { }
    Operation(const int &idx_, const int &x_, const int &y_, const int &val_) {
        idx = idx_;
        x = x_;
        y = y_;
        val = val_;
    }
    bool operator<(const Operation &rhs) const {
        return idx < rhs.idx;
    }
}ope[kMaxM], tmp[kMaxM];

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("strings.in", "r", stdin);
    freopen("strings.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif  // ONLINE_JUDGE

    return 0;
}
