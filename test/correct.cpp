/* URL: http://www.cnblogs.com/sagitta/p/5982251.html */
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, Q = 1e5 + 10, A = N + Q * 2, lim = 1e9;
struct operate {
    int x, y, k, cnt, num;
    operate() { }
    operate(int _x, int _y, int _k, int _cnt, int _num) {
        x = _x;
        y = _y;
        k = _k;
        cnt = _cnt;
        num = _num;
    }
}a[A], q1[A], q2[A];
int raw[N], ans[Q], sum[N];
int n, m, len, l1, l2;
void update(int x, int y) {
    for (int i = x; i <= n; i += (i & -i))
        sum[i] += y;
}
int query(int x) {
    int re = 0;
    for (int i = x; i; i -= (i & -i))
        re += sum[i];
    return re;
}
void calc(int ll, int rr, int rawl, int mid) {
    for (int i = ll; i <= rr; ++i) {
        if (a[i].k)
            a[i].cnt = query(a[i].y) - query(a[i].x - 1);
        else if (a[i].y <= mid)
            update(a[i].x, a[i].cnt);
    }
    for (int i = ll; i <= rr; ++i)
        if (!a[i].k && a[i].y <= mid)
            update(a[i].x, -a[i].cnt);
    l1 = l2 = 0;
    for (int i = ll; i <= rr; ++i)
        if (a[i].k) {
            if (a[i].k <= a[i].cnt)
                q1[++l1] = a[i];
            else {
                a[i].k -= a[i].cnt;
                q2[++l2] = a[i];
            }
        } else {
            if (a[i].y <= mid)
                q1[++l1] = a[i];
            else
                q2[++l2] = a[i];
        }
    int now = ll;
    for (int i = 1; i <= l1; ++i)
        a[now++] = q1[i];
    for (int i = 1; i <= l2; ++i)
        a[now++] = q2[i];
}
void divide(int ll, int rr, int rawl, int rawr) {
    if (rawl == rawr) {
        for (int i = ll; i <= rr; ++i)
            if (a[i].k)
                ans[a[i].num] = rawl;
        return;
    }
    int mid = (rawl + rawr) >> 1;
    calc(ll, rr, rawl, mid);
    int tmp = l1;
    if (tmp)
        divide(ll, ll + tmp - 1, rawl, mid);
    if (ll + tmp <= rr)
        divide(ll + tmp, rr, mid + 1, rawr);
}
int main() {
    while (scanf("%d", &n) != EOF) {
        len = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &raw[i]);
            a[++len] = operate(i, raw[i], 0, 1, 0);
        }
        scanf("%d", &m);
        int op, x, y, z;
        for (int i = 1; i <= m; ++i) {
            scanf("%d", &op);
            if (op & 1) {
                scanf("%d%d", &x, &y);
                a[++len] = operate(x, raw[x], 0, -1, 0);
                a[++len] = operate(x, y, 0, 1, 0);
                raw[x] = y;
                ans[i] = 0;
            } else {
                scanf("%d%d%d", &x, &y, &z);
                a[++len] = operate(x, y, z, 0, i);
            }
        }
        divide(1, len, 1, lim);
        for (int i = 1; i <= m; ++i)
            if (ans[i])
                printf("%d\n", ans[i]);
    }
    return 0;
}