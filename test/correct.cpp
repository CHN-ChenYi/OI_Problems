//#pragma GCC optimize(3)
#include "bits/stdc++.h"
using namespace std;
//#define SHOW_CONSOLE
//#include <EGE.h>
namespace io {
#define USE_FEAD_IO
#ifdef USE_FEAD_IO
#define BUF_SIZE 5000010
    char buf[BUF_SIZE]; int cur = BUF_SIZE; FILE *in = stdin;
    inline char gnc() {
        if (cur == BUF_SIZE) { fread(buf, BUF_SIZE, 1, in); cur = 0; }
        return buf[cur++];
    }
#else
    inline char gnc() {
        return (char)getchar();
    }
#endif
    template<typename T>
    inline void gi(T &dx) {
        dx = 0;
        int yc = gnc();
        bool nega = false;
        while (yc < '0' || yc > '9') { nega = (yc == '-' ? true : nega); yc = gnc(); }
        while (yc >= '0' && yc <= '9') { dx = (T)(dx * 10 + yc - '0'); yc = gnc(); }
        if (nega) { dx = -dx; }
    }
    void gc(char &a) {
        do a = gnc(); while (!isgraph(a));
    }
#if __cplusplus >= 201103l || (defined(_MSVC_LANG) && _MSVC_LANG >= 201103l)
    template<typename T, typename ...Args> inline void gi(T &a, Args &...args) {
        gi(a); gi(args...);
    }
#else
    template<typename t1, typename t2> inline void gi(t1 &a, t2 &b) { gi(a); gi(b); }
    template<typename t1, typename t2, typename t3> inline void gi(t1 &a, t2 &b, t3 &c) { gi(a); gi(b); gi(c); }
    template<typename t1, typename t2, typename t3, typename t4> inline void gi(t1 &a, t2 &b, t3 &c, t4 &d) { gi(a); gi(b); gi(c); gi(d); }
    template<typename t1, typename t2, typename t3, typename t4, typename t5> inline void gi(t1 &a, t2 &b, t3 &c, t4 &d, t5 &e) { gi(a); gi(b); gi(c); gi(d); gi(e); }
#endif
}
using namespace io;
typedef unsigned long long ll;

struct ufset {
    int fa[20];
    int f(int x) {
        if (fa[x] <= 0) return x;
        return fa[x] = f(fa[x]);
    }
    int operator[](int x) { return f(x); }
    bool merge(int x, int y) {
        if ((x = f(x)) == (y = f(y))) return false;
        fa[y] = x; return true;
    }
    ufset() { memset(fa, -1, sizeof fa); }
} uf;

int n, k;
struct qj_t {
    ll l, r;
};
vector<qj_t> qj;
ll po[20];
int gb(ll x, int w) {
    return ((x % po[w + 1]) / po[w]) % 10;
}
bool qjin(qj_t a, qj_t b) {
    return b.l <= a.l && a.l <= a.r && a.r < b.r;
}
bool qjin(ll al, ll ar, ll bl, ll br) {
    return bl <= al && al <= ar && ar <= br;
}
bool ok(int u, int v, int w) {
    if (u == v) return true;
    if (u < v) { // 变大
        ll d = (v - u) * po[w];
        for (int i = 1, j = 1; i <= n; ++i) {
            ll l = qj[i].l, r = qj[i].r;
            ll el, er;
            int s = gb(r, w);
            // assume that s >= u
            el = r / po[w] * po[w] - s * po[w] + u * po[w];
            er = el + po[w] - 1;
            if (s < u) {
                el -= po[w + 1];
                er -= po[w + 1];
            }
            if (el < l) el = l;
            if (er > r) er = r;
            if (el < 0) el = 0;
            if (el > er) continue;
            el += d; er += d;
            while (j <= n && !qjin(el, er, qj[j].l, qj[j].r)) ++j;
            if (j > n || !qjin(el, er, qj[j].l, qj[j].r)) return false;
        }
    } else {
        ll d = (u - v) * po[w];
        for (int i = n, j = n; i >= 1; --i) {
            ll l = qj[i].l, r = qj[i].r;
            ll el, er;
            int s = gb(l, w);
            // assume that s <= u
            el = l / po[w] * po[w] - s * po[w] + u * po[w];
            er = el + po[w] - 1;
            if (s > u) {
                el += po[w + 1];
                er += po[w + 1];
            }
            if (el < l) el = l;
            if (er > r) er = r;
            if (el < 0) el = 0;
            if (el > er) continue;
            el -= d; er -= d;
            while (j >= 1 && !qjin(el, er, qj[j].l, qj[j].r)) --j;
            if (j < 1 || !qjin(el, er, qj[j].l, qj[j].r)) return false;
        }
    }
    return true;
}
bool ok(int u, int v) {
    for (int i = 0; i < k; ++i) {
        if (!ok(u, v, i)) return false;
    }
    return true;
}
bool ou[10];
int main() {
    freopen("laser.in", "r", stdin);
    freopen("laser.out", "w", stdout);
    po[0] = 1;
    for (int i = 1; i <= 19; ++i) po[i] = po[i - 1] * 10;
    gi(n, k);
    qj.push_back(qj_t({0,(1ULL << 64) - 1}));
    for (int i = 1; i <= n; ++i) {
        ll l, r; gi(l, r);
        if (!qj.empty() && qj.back().r == l - 1) qj.back().r = r;
        else qj.push_back(qj_t({l,r}));
    }
    n = qj.size() - 1;
    for (int i = 1; i <= 9; ++i) {
        for (int j = i + 1; j <= 9; ++j) {
            if (uf[i] == uf[j]) continue;
            if (ok(i, j) && ok(j, i)) uf.merge(i, j);
        }
    }
    for (int i = 1; i <= 9; ++i) {
        if (ou[i]) continue;
        for (int j = i; j <= 9; ++j) {
            if (ou[j]) continue;
            if (uf[i] != uf[j]) continue;
            ou[j] = true;
            putchar('0' + j);
        }
        putchar('\n');
    }
    return 0;
}
