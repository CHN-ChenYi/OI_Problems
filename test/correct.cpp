#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
typedef long long ll;
set<int> app[100005];
int arr[100005], cnt, n, q;
ll ans[100005];
char str[15];
struct query_tp {
    int idx, x, y, val;
    query_tp() {
    }
    query_tp(int _idx, int _x, int _y, int _val) {
        idx = _idx;
        x = _x;
        y = _y;
        val = _val;
    }
    inline bool operator <(const query_tp &a) const {
        if (x == a.x)
            return idx < a.idx;
        return x < a.x;
    }
} query[1000005], tmp[1000005];
struct Fenwick_tree {
    ll seg[100005];
    inline void modify(int x, int num) {
        for (; x <= n; x += x & -x)
            seg[x] += num;
    }
    inline ll query(int x) {
        ll res = 0;
        for (; x; x -= x & -x)
            res += seg[x];
        return res;
    }
    inline void reset(int x) {
        for (; x <= n; x += x & -x)
            seg[x] = 0;
    }
} seg;
inline void modify(int x, int y) {
    if (arr[x] == y)
        return;
    if (arr[x]) {
        set<int>::iterator it = app[arr[x]].find(x);
        int pos = 0;
        if (it != app[arr[x]].begin()) {
            pos = *(--it);
            it++;
            query[cnt++] = query_tp(0, x, pos, pos - x);
        }
        it++;
        if (it != app[arr[x]].end()) {
            query[cnt++] = query_tp(0, *it, x, x - *it);
            if (pos)
                query[cnt++] = query_tp(0, *it, pos, *it - pos);
        }
        app[arr[x]].erase(x);
    }
    app[y].insert(x);
    set<int>::iterator it = app[y].find(x);
    int pos = 0;
    if (it != app[y].begin()) {
        pos = *(--it);
        it++;
        query[cnt++] = query_tp(0, x, pos, x - pos);
    }
    it++;
    if (it != app[y].end()) {
        query[cnt++] = query_tp(0, *it, x, *it - x);
        if (pos)
            query[cnt++] = query_tp(0, *it, pos, pos - *it);
    }
    arr[x] = y;
}
inline void add_query(int idx, int x, int y) {
    query[cnt++] = query_tp(idx, x - 1, x - 1, 1);
    query[cnt++] = query_tp(idx, y, y, 1);
    query[cnt++] = query_tp(idx, x - 1, y, -1);
    query[cnt++] = query_tp(idx, y, x - 1, -1);
}
void calc(int l, int r) {
    if (l >= r)
        return;
    int m = l + r >> 1;
    calc(l, m);
    calc(m + 1, r);
    int lp = l, rp = m + 1, cur = l;
    while (lp <= m && rp <= r) {
        if (query[lp] < query[rp]) {
            if (!query[lp].idx)
                seg.modify(query[lp].y, query[lp].val);
            tmp[cur++] = query[lp++];
        } else {
            if (query[rp].idx)
                ans[query[rp].idx] += seg.query(query[rp].y) * query[rp].val;
            tmp[cur++] = query[rp++];
        }
    }
    while (lp <= m) {
        if (!query[lp].idx)
            seg.modify(query[lp].y, query[lp].val);
        tmp[cur++] = query[lp++];
    }
    while (rp <= r) {
        if (query[rp].idx)
            ans[query[rp].idx] += seg.query(query[rp].y) * query[rp].val;
        tmp[cur++] = query[rp++];
    }
    for (int i = l; i <= r; i++) {
        query[i] = tmp[i];
        if (!query[i].idx)
            seg.reset(query[i].y);
    }
}
int main() {
    freopen("strings.in", "r", stdin);
    freopen("strings.out", "wt", stdout);
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        modify(i, x);
    }
    int tot = 0;
    while (q--) {
        int x, y;
        scanf("%s%d%d", str, &x, &y);
        if (str[0] == 'Q')
            add_query(++tot, x, y);
        else
            modify(x, y);
    }
    calc(0, cnt - 1);
    for (int i = 1; i <= tot; i++)
        printf("%lld\n", ans[i]);
    return 0;
}
