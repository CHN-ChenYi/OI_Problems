/* URL: http://www.cnblogs.com/sagitta/p/5982251.html */
//#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10, Q = 5e3 + 10, lim = 1e9;
struct point {
    int x, num;
}a[N];
struct query {
    int x, y, k, cnt, num;
}q[Q], b[Q];
int sum[N], ans[Q];
int n, m;
bool cmp(const point &aa, const point &bb) {
    return aa.x < bb.x;
}
void calc(int ll, int rr, int rawL, int mid) {
    int L = 1, R = n + 1, MID;
    while (L < R) {
        MID = (L + R) >> 1;
        if (a[MID].x >= rawL)
            R = MID;
        else
            L = MID + 1;
    }
    for (int i = R; i <= n && a[i].x <= mid; ++i)
        for (int j = a[i].num; j <= n; j += (j & -j))
            ++sum[j];
    for (int i = ll; i <= rr; ++i) {
        q[i].cnt = 0;
        for (int j = q[i].y; j; j -= (j & -j))
            q[i].cnt += sum[j];
        for (int j = q[i].x - 1; j; j -= (j & -j))
            q[i].cnt -= sum[j];
    }
    for (int i = R; i <= n && a[i].x <= mid; ++i)
        for (int j = a[i].num; j <= n; j += (j & -j))
            --sum[j];
}
void divide(int ll, int rr, int rawL, int rawR) {
    if (rawL == rawR) {
        for (int i = ll; i <= rr; ++i)
            ans[q[i].num] = rawR;
        return;
    }
    int mid = rawL + ((rawR - rawL) >> 1);
    calc(ll, rr, rawL, mid);
    int now1 = ll, now2 = rr;
    for (int i = ll; i <= rr; ++i) {
        if (q[i].cnt >= q[i].k)
            b[now1++] = q[i];
        else {
            q[i].k -= q[i].cnt;
            b[now2--] = q[i];
        }
    }
    for (int i = ll; i <= rr; ++i)
        q[i] = b[i];
    if (now1 != ll)
        divide(ll, now1 - 1, rawL, mid);
    if (now2 != rr)
        divide(now2 + 1, rr, mid + 1, rawR);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i].x);
        a[i].num = i;
    }
    a[n + 1].x = 2e9;
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &q[i].x, &q[i].y, &q[i].k);
        q[i].num = i;
    }
    divide(1, m, -lim, lim);
    for (int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}