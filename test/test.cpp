/*
Name: CRB(HDU5412)
Author: godwings
Date: 12/09/2017
*/
#include <cctype>
#include <cstdio>
#include <cstring>
const int inf = 0x3fffffff;
const int kMaxN = 3e5 + 10;

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
struct Operate {
    int id;
    bool type; // 0 for modify, 1 for query
    int pos, key;
    int l, r, k, cnt;
    Operate() {
        memset(this, 0, sizeof(Operate));
    }
    Operate(const int pos_, const int key_, const int cnt_) {
        type = 0;
        pos = pos_;
        key = key_;
        cnt = cnt_;
    }
    Operate(const int id_, const int l_, const int r_, const int k_) {
        type = 1;
        id = id_;
        l = l_;
        r = r_;
        k = k_;
        cnt = 0;
    }
}ope[kMaxN], tmp[kMaxN];
int a[kMaxN], tot;
int ans[kMaxN];

struct BIT {
 private:
    int tr[kMaxN];
    inline int lowerbit(const int x) {
        return x & -x;
    }

 public:
    void Modify(const int pos, const int delta) {
        for (int i = pos; i <= n; i += lowerbit(i))
            tr[i] += delta;
    }
    int Query(const int left, const int right) {
        int ret = 0;
        for (int i = right; i; i -= lowerbit(i))
            ret += tr[i];
        for (int i = left - 1; i; i -= lowerbit(i))
            ret -= tr[i];
        return ret;
    }
}T;
void Calc(const int ope_id_l, const int ope_id_r, const int ans_l, const int ans_r) {
    for (int i = ope_id_l; i <= ope_id_r; i++) {
        if (ope[i].type)
            ope[i].cnt = T.Query(ope[i].l, ope[i].r);
        else if (ope[i].key <= ans_r)
            T.Modify(ope[i].pos, ope[i].cnt);
    }

}
void OverallDichotomy(const int ope_id_l, const int ope_id_r, const int ans_l, const int ans_r) {
    if (ans_l == ans_r) {
        for (int i = ope_id_l; i <= ope_id_r; i++)
            ans[ope[ope_id_l].id] = ans_l;
        return;
    }
    const int ans_mid = (ans_l + ans_r) >> 1;
    Calc(ope_id_l, ope_id_r, ans_l, ans_mid);

}

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("CRB.in", "r", stdin);
    freopen("CRB.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    while (scanf("%d", &n) != EOF) {
        tot = 0;
        memset(ans, 0, sizeof ans);
        for (int i = 1; i <= n; i++) {
            scan(a[i]);
            ope[++tot] = Operate(i, a[i], 1);
        }
        scan(m);
        for (int i = 1, op, x, y, z; i <= m; i++) {
            scan(op);
            if (op == 1) {
                scan(x, y);
                ope[++tot] = Operate(i, a[i], -1);
                a[i] = x;
                ope[++tot] = Operate(i, a[i], 1);
            } else {
                scan(x, y, z);
                ope[++tot] = Operate(i, x, y, z);
            }
        }
        OverallDichotomy(1, tot, -inf, inf);
        for (int i = 1; i <= m; i++) {
            if (ans[i])
                printf("%d\n", ans[i]);
        }
    }
    return 0;
}
