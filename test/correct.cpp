#include <cstdio>
#include <vector>
#include <algorithm>
using std::min;
using std::swap;
using std::pair;
using std::vector;

#include <cctype>
template <class T>
inline void scan(T &x) {
    x = 0;
    char c;
    while (isdigit(c = getchar()) == 0) { }
    for (; isdigit(c) != 0; c = getchar())
        x = x * 10 + (c & 0xf);
}
template <class T>
inline void scan(T &x, T &y) {
    scan(x); scan(y);
}
template <class T>
inline void scan(T &x, T &y, T &z) {
    scan(x); scan(y); scan(z);
}

typedef pair<int, int> Pii;
vector<Pii> adj[100086];
bool vis[100086];

int fa[17][100086], dep[100086], len[100086];
int ss, st, sw;
inline void dfs(int x, int p, int d, int l) {
    vis[x] = 1;
    dep[x] = d;
    len[x] = l;
    fa[0][x] = p;
    for (vector<Pii>::iterator it = adj[x].begin(); it != adj[x].end(); it++) {
        if (it->first != p) {
            if (vis[it->first]) {
                ss = x;
                st = it->first;
                sw = it->second;
            } else {
                dfs(it->first, x, d + 1, l + it->second);
            }
        }
    }
}

inline int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    int dx = dep[x] - dep[y];
    for (int i = 0; i <= 16; i++) {
        if (dx & (1 << i))
            x = fa[i][x];
    }
    for (int i = 16; i >= 0; i--) {
        if (fa[i][x] != fa[i][y]) {
            x = fa[i][x];
            y = fa[i][y];
        }
    }
    if (x == y)
        return x;
    else
        return fa[0][x];
}
int tree_three(int x, int y, int z) {
    int l = lca(x, y), o = lca(x, z);
    if (dep[o] < dep[l]) {
        return len[x] + len[y] + len[z] - len[l] - 2 * len[o];
    } else if (dep[o] > dep[l]) {
        return len[x] + len[y] + len[z] - 2 * len[l] - len[o];
    } else {
        int p = lca(y, z);
        if (dep[p] < dep[l])
            return printf("ORZ MYC?\n"), -233;
        else if (dep[p] > dep[l])
            return len[x] + len[y] + len[z] - 2 * len[l] - len[p];
        else
            return len[x] + len[y] + len[z] - 3 * len[l];
    }
}

inline int dist(int x, int y) {
    return len[x] + len[y] - (len[lca(x, y)] << 1);
}

int cactus_three(int x, int y, int z) {
    int ans = tree_three(x, y, z);
    ans = min(ans, sw + dist(x, ss) + tree_three(st, y, z));
    ans = min(ans, sw + dist(x, st) + tree_three(ss, y, z));
    ans = min(ans, sw + dist(y, ss) + tree_three(x, st, z));
    ans = min(ans, sw + dist(y, st) + tree_three(x, ss, z));
    ans = min(ans, sw + dist(z, ss) + tree_three(x, y, st));
    ans = min(ans, sw + dist(z, st) + tree_three(x, y, ss));
    return ans;
}

int n, m, q;

int main() {
    freopen("three.in", "r", stdin);
    freopen("three.out", "w", stdout);
    scan(n, m, q);
    for (int i = 1, s, t, w; i <= m; i++) {
        scan(s, t, w);
        adj[s].push_back(Pii(t, w));
        adj[t].push_back(Pii(s, w));
    }
    dfs(1, 0, 1, 0);
    for (int j = 1; j <= 16; j++) {
        for (int i = 1; i <= n; i++)
            fa[j][i] = fa[j - 1][fa[j - 1][i]];
    }
    for (int i = 1, x, y, z; i <= q; i++) {
        scan(x, y, z);
        printf("%d\n", m == n ? cactus_three(x, y, z) : tree_three(x, y, z));
    }
    return 0;
}
