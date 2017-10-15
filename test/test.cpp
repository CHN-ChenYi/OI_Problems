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

struct BinaryIndexedTree {
 private:
    int n;
    LL tr[kMaxN];
    inline int lowbit(const int &x) {
        return x & -x;
    }

 public:
    inline void Init(const int &n_) {
        n = n_;
    }
    inline void Reset(int pos) {
        while (pos <= n) {
            tr[pos] = 0;
            pos += lowbit(pos);
        }
    }
    inline void Modify(int pos, const int &del) {
        while (pos <= n) {
            tr[pos] += del;
            pos += lowbit(pos);
        }
    }
    inline LL Query(int pos) {
        LL ret = 0;
        while (pos) {
            ret += tr[pos];
            pos -= lowbit(pos);
        }
        return ret;
    }
}BIT;

int n, m;
int ans_tot;
int a[kMaxN];
char str[20];
LL ans[kMaxN];
set<int> s[kMaxN];

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
        return x != rhs.x ? x < rhs.x : idx < rhs.idx;
    }
}ope[kMaxM], tmp[kMaxM]; int ope_tot;
inline void Modify(const int &pos, const int &val) {
    if (a[pos]) {
        int x = 0;
        set<int>::iterator it = s[a[pos]].find(pos);
        if (it != s[a[pos]].begin()) {
            x = *(--it);
            it++;
            ope[++ope_tot] = Operation(0, pos, x, x - pos);
        }
        it++;
        if (it != s[a[pos]].end()) {
            ope[++ope_tot] = Operation(0, *it, pos, pos - *it);
            if (x)
                ope[++ope_tot] = Operation(0, *it, x, *it - x);
        }
        s[a[pos]].erase(x);
    }
    s[val].insert(pos);
    set<int>::iterator it = s[val].find(pos);
    int x = 0;
    if (it != s[val].begin()) {
        x = *(--it);
        it++;
        ope[++ope_tot] = Operation(0, pos, x, pos - x);
    }
    it++;
    if (it != s[val].end()) {
        ope[++ope_tot] = Operation(0, *it, pos, *it - pos);
        if (x)
            ope[++ope_tot] = Operation(0, *it, x, x - *it);
    }
    a[pos] = val;
}
inline void Query(const int &idx, const int &l, const int &r) {
    ope[++ope_tot] = Operation(idx, l - 1, l - 1, 1);
    ope[++ope_tot] = Operation(idx, r, r, 1);
    ope[++ope_tot] = Operation(idx, l - 1, r, -1);
    ope[++ope_tot] = Operation(idx, l, l - 1, -1);
}

void CDQ(const int &l, const int &r) {
    if (l == r)
        return;
    const int m = (l + r) >> 1;
    CDQ(l, m); CDQ(m + 1, r);
    for (int i = l, left_ptr = l, right_ptr = m + 1; i <= r; i++) {
        if (left_ptr <= m && (right_ptr > r || ope[left_ptr] < ope[right_ptr])) {
            if (!ope[left_ptr].idx)
                BIT.Modify(ope[left_ptr].y, ope[left_ptr].val);
            tmp[i] = ope[left_ptr++];
        } else {
            if (ope[right_ptr].idx)
                ans[ope[right_ptr].idx] += BIT.Query(ope[right_ptr].y) * ope[right_ptr].val;
            tmp[i] = ope[right_ptr++];
        }
    }
    for (int i = l; i <= m; i++) {
        if (!ope[i].idx)
            BIT.Reset(ope[i].y);
    }
    memcpy(ope, tmp, (r - l + 1) * sizeof(Operation));
}

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("strings.in", "r", stdin);
    freopen("strings.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif  // ONLINE_JUDGE
    scan(n, m);
    BIT.Init(n);
    for (int i = 1, x; i <= n; i++) {
        scan(x);
        Modify(i, x);
    }
    for (int i = 1, x, y; i <= m; i++) {
        scanf("%s", str);
        scan(x, y);
        if (str[0] == 'Q')
            Query(++ans_tot, x, y);
        else
            Modify(x, y);
    }
    CDQ(1, ope_tot);
    for (int i = 1; i <= ans_tot; i++)
        printf("%lld\n", ans[i]);
    return 0;
}
