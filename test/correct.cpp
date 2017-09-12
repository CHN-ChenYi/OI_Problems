/* URL: http://www.cnblogs.com/sagitta/p/5982251.html */
//#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10, Q = 5e3 + 10, lim = 1e9;
struct point {
    int x, id;
    bool operator<(const point rhs) const {
        return x < rhs.x;
    }
}a[N];
struct query {
    int l, r, k, cnt, id;
}q[Q], tmp[Q];
int tr[N], ans[Q];
int n, m;
inline int lowerbit(const int x) {
    return x & -x;
}
void Calc(int q_id_l, int q_id_r, int ans_l, int ans_r) {
    const int pos = lower_bound(a + 1, a + n + 1, point{ans_l, 0}) - a;
    for (int i = pos; i <= n && a[i].x <= ans_r; ++i) {
        for (int j = a[i].id; j <= n; j += lowerbit(j))
            ++tr[j];
    }
    for (int i = q_id_l; i <= q_id_r; ++i) {
        q[i].cnt = 0;
        for (int j = q[i].r; j; j -= lowerbit(j))
            q[i].cnt += tr[j];
        for (int j = q[i].l - 1; j; j -= lowerbit(j))
            q[i].cnt -= tr[j];
    }
    for (int i = pos; i <= n && a[i].x <= ans_r; ++i) {
        for (int j = a[i].id; j <= n; j += lowerbit(j))
            --tr[j];
    }
}
void OverallDichotomy(int q_id_l, int q_id_r, int ans_l, int ans_r) {
    if (ans_l == ans_r) {
        for (int i = q_id_l; i <= q_id_r; ++i)
            ans[q[i].id] = ans_r;
        return;
    }
    int ans_mid = ans_l + ((ans_r - ans_l) >> 1);
    Calc(q_id_l, q_id_r, ans_l, ans_mid);
    int left_ptr = q_id_l, right_ptr = q_id_r;
    for (int i = q_id_l; i <= q_id_r; ++i) {
        if (q[i].cnt >= q[i].k)
            tmp[left_ptr++] = q[i];
        else {
            q[i].k -= q[i].cnt;
            tmp[right_ptr--] = q[i];
        }
    }
    memcpy(q + q_id_l, tmp + q_id_l, (q_id_r - q_id_l + 1) * sizeof(query));
    if (left_ptr != q_id_l)
        OverallDichotomy(q_id_l, left_ptr - 1, ans_l, ans_mid);
    if (right_ptr != q_id_r)
        OverallDichotomy(right_ptr + 1, q_id_r, ans_mid + 1, ans_r);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i].x);
        a[i].id = i;
    }
    a[n + 1].x = 2e9;
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].k);
        q[i].id = i;
    }
    OverallDichotomy(1, m, -lim, lim);
    for (int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}