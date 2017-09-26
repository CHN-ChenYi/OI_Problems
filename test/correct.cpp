/* URL: http://blog.csdn.net/bahuia/article/details/54907818 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 50005;
const int MAXM = 40005;
const int MAXQ = MAXM * 2 + MAXN;

struct Query {
    int type, pos, val;
    bool operator < (const Query &rhs) const {
        return pos == rhs.pos ? type < rhs.type : pos < rhs.pos;  // 同一位置，修改操作要先于查询操作
    }
}que[MAXQ], tmp[MAXQ];

int ans[MAXQ];
int qnum, anum;     // qnum表示所有有序对的个数，anum表示询问操作的个数

void cdq(int l, int r) {
    if (l + 1 >= r) return;
    int m = (l + r) >> 1;
    cdq(l, m); cdq(m, r);
    int p = l, q = m, cnt = 0, sum = 0;
    while (p < m && q < r) {         // 类似归并排序的模式，换成了处理有序对
        if (que[p] < que[q]) {
            if (que[p].type == 1) sum += que[p].val;   // 左半部分先发生的修改操作，保存变化量的和sum
            tmp[cnt++] = que[p++];
        } else {
            if (que[q].type == 2) ans[que[q].val] -= sum;       // 左端点查询减去sum
            else if (que[q].type == 3) ans[que[q].val] += sum;      // 右端点查询加上sum
            tmp[cnt++] = que[q++];
        }
    }
    while (p < m) tmp[cnt++] = que[p++];
    while (q < r) {
        if (que[q].type == 2) ans[que[q].val] -= sum;
        else if (que[q].type == 3) ans[que[q].val] += sum;
        tmp[cnt++] = que[q++];
    }
    for (int i = 0; i < cnt; i++)       // 利用临时数组更新操作数组que
        que[i + l] = tmp[i];
}

char op[10];

int main() {
    //freopen("in.txt", "r", stdin);
    int T, cs = 0;
    scanf("%d", &T);
    while (T--) {
        int n, x;
        scanf("%d", &n);
        qnum = anum = 0;
        for (int i = 1; i <= n; i++, qnum++) {
            scanf("%d", &x);
            que[qnum] = (Query) { 1, i, x };
        }
        while (true) {
            scanf("%s", op);
            if (op[0] == 'E') break;
            if (op[0] == 'Q') {
                int l, r;
                scanf("%d%d", &l, &r);
                que[qnum++] = (Query) { 2, l - 1, anum };
                que[qnum++] = (Query) { 3, r, anum++ };
            } else {
                int pos, add;
                scanf("%d%d", &pos, &add);
                add *= (op[0] == 'A' ? 1 : -1);
                que[qnum++] = (Query) { 1, pos, add };
            }
        }
        memset(ans, 0, sizeof(ans));      // 记得ans清零
        cdq(0, qnum);
        printf("Case %d:\n", ++cs);
        for (int i = 0; i < anum; i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}
