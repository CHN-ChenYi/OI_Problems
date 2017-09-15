#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define inf 1000000000
#define pa pair<int,int>
#define ll long long 
#define mod 45989
using namespace std;
int read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch<'0' || ch>'9') { if (ch == '-')f = -1; ch = getchar(); }
    while (ch >= '0'&&ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x*f;
}
int bin[20];
int n, m, cnt;
int dis[100005], last[100005];
int f[100005][16], g[100005], t[16];
struct edge {
    int to, next, v;
}e[200005];
void insert(int u, int v, int w) {
    e[++cnt].to = v; e[cnt].next = last[u]; last[u] = cnt; e[cnt].v = w;
    e[++cnt].to = u; e[cnt].next = last[v]; last[v] = cnt; e[cnt].v = w;
}
void dfs1(int x, int fa) {
    for (int i = last[x]; i; i = e[i].next)
        if (e[i].to != fa) {
            dfs1(e[i].to, x);
            g[x] += g[e[i].to] + e[i].v / 16;
            f[x][e[i].v % 16]++;
            for (int j = 0; j<16; j++) {
                int k = j + e[i].v;
                g[x] += k / 16 * f[e[i].to][j];
                f[x][k % 16] += f[e[i].to][j];
            }
        }
}
void dfs2(int x, int fa) {
    for (int i = last[x]; i; i = e[i].next)
        if (e[i].to != fa) {
            int tmp = g[x] - g[e[i].to];
            for (int j = 0; j<16; j++) {
                int k = j + e[i].v;
                tmp -= k / 16 * f[e[i].to][j];
                t[k % 16] = f[x][k % 16] - f[e[i].to][j];
            }
            t[e[i].v % 16]--;
            g[e[i].to] += tmp;
            f[e[i].to][e[i].v % 16]++;
            for (int j = 0; j<16; j++) {
                int k = j + e[i].v;
                g[e[i].to] += k / 16 * t[j];
                f[e[i].to][k % 16] += t[j];
            }
            dfs2(e[i].to, x);
        }
}
int main() {
    freopen("warehouse.in", "r", stdin);
    freopen("warehouse.ans", "w", stdout);
    bin[0] = 1;
    for (int i = 1; i<20; i++)bin[i] = bin[i - 1] << 1;
    n = read(), m = read();
    for (int i = 1; i<n; i++) {
        int u = read(), v = read(), w = read();
        insert(u, v, w);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        ll ans = g[i] * 16;
        for (int j = 0; j<16; j++)ans += (j^m)*f[i][j];
        printf("%I64d\n", ans);
    }
    return 0;
}