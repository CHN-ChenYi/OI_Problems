/* URL: http://www.cnblogs.com/bin-gege/p/6052449.html */
#include<bits/stdc++.h>
#define F(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

const int N = 1e5 + 7;
int t, n, sum[N];

struct node {
    int x, y, z, cnt, id;
    bool operator < (const node &b)const {
        if (x == b.x && y == b.y)
            return z < b.z;
        if (x == b.x)
            return y < b.y;
        return x < b.x;
    }
    bool operator == (const node &b)const {
        return x == b.x && y == b.y && z == b.z;
    }
}a[N], b[N];

bool cmp(node a, node b) {
    return a.id < b.id;
}

inline void add(int x, int c) { while (x < N)sum[x] += c, x += x&-x; }
inline  int ask(int x) { int an = 0; while (x)an += sum[x], x -= x&-x; return an; }

void solve(int l, int r) {
    if (l == r)return;
    int mid = l + r >> 1;
    solve(l, mid), solve(mid + 1, r);
    for (int i = l, j = l, k = mid + 1; i <= r; i++) {
        if ((a[j].y <= a[k].y || r < k) && j <= mid)
            b[i] = a[j++], add(b[i].z, 1);
        else
            b[i] = a[k++], b[i].cnt += ask(b[i].z);
    }//当左半边的y大于当前右半边的y时，先将这个点更新了，这样就保证了前面的y都是比这个点小
    F(i, l, mid)
        add(a[i].z, -1), a[i] = b[i];
    F(i, mid + 1, r)
        a[i] = b[i];
}

int main() {
    freopen("test.in", "r", stdin);
    freopen("test.ans", "w", stdout);
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        F(i, 1, n) {
            scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
            a[i].id = i, a[i].cnt = 0;
        }
        sort(a + 1, a + 1 + n);
        for (int i = n - 1; i > 0; i--)
            if (a[i] == a[i + 1])
                a[i].cnt = a[i + 1].cnt + 1;
        solve(1, n);
        sort(a + 1, a + 1 + n, cmp);
        F(i, 1, n)
            printf("%d\n", a[i].cnt);
    }
    return 0;
}