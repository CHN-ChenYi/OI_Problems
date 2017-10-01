/*
Name: economic(LJOJ4548)
Author: godwings
Date: 01/10/2017
*/
#include <cctype>
#include <cstdio>
#include <vector>
#include <algorithm>
using std::max;
using std::vector;

const int kMaxN = 20;
const int kMaxM = 1 << 8;

typedef std::pair<double, double> par;
typedef std::vector<par> vec;

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

int T;
int n;
double W;
int a[kMaxN];
vec len[kMaxM];
int weight[kMaxM];

void DFS(vec &now, const int l, const int r, const int s) {

}

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("economic.in", "r", stdin);
    freopen("economic.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(T);
    while (T--) {
        scanf("%lf", &W); scan(n);
        for (int i = 1; i <= n; i++)
            scan(a[i]);
        const int lim = (1 << n) - 1;
        for (int i = lim; i >= 0; i--)
            len[i].clear();
        for (int i = 1; i <= n; ++i) {
            len[1 << (i - 1)].push_back(par(0, 0));
            weight[1 << (i - 1)] = a[i];
        }
        for (int s = 0; s <= lim; s++) {
            if ((s & -s) != s) {
                DFS(len[s], 0, 0, s);
                weight[s] = weight[s & -s] + weight[s ^ (s & -s)];
            }
        }
        const vec &ans_vec = len[lim];
        double ans = -1;
        for (int i = ans_vec.size() - 1; i >= 0; i--)
            ans = max(ans, ans_vec[i].first + ans_vec[i].second);
        if (ans == -1)
            puts("-1");
        else
            printf("%.10lf\n", ans);
    }
    return 0;
}
