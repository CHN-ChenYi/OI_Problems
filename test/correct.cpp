/* URL: https://oi.men.ci/noi2014-forest/ */
#include <cstdio>
#include <climits>
#include <cassert>
#include <algorithm>

const int MAXN = 50000;
const int MAXM = 100000;

struct LinkCutTree {
    struct Node {
        Node *c[2], *p, *pp, *max;
        int w;
        bool rev;

        Node() : p(NULL), pp(NULL), max(this), w(0) {}

        int relation() { return this == p->c[0] ? 0 : 1; }

        void maintain() {
            max = this;
            if (c[0] && c[0]->max->w > max->w) max = c[0]->max;
            if (c[1] && c[1]->max->w > max->w) max = c[1]->max;
        }

        void pushDown() {
            if (rev) {
                std::swap(c[0], c[1]);
                if (c[0]) c[0]->rev ^= 1;
                if (c[1]) c[1]->rev ^= 1;
                rev = false;
            }
        }

        void rotate() {
            std::swap(pp, p->pp);
            int r = relation();
            Node *o = p;

            p = o->p;
            if (o->p) o->p->c[o->relation()] = this;

            o->c[r] = c[r ^ 1];
            if (c[r ^ 1]) c[r ^ 1]->p = o;

            c[r ^ 1] = o;
            o->p = this;

            o->maintain(), maintain();
        }

        void splay() {
            while (p) {
                if (p->p) p->p->pushDown();
                p->pushDown(), pushDown();

                if (!p->p) rotate();
                else if (p->relation() == relation()) p->rotate(), rotate();
                else rotate(), rotate();
            }
            pushDown();
        }

        void expose() {
            splay();
            if (c[1]) {
                std::swap(c[1]->p, c[1]->pp);
                c[1] = NULL;
                maintain();
            }
        }

        bool splice() {
            splay();
            if (!pp) return false;
            pp->expose();
            pp->c[1] = this;
            pp->maintain();
            std::swap(p, pp);
            return true;
        }

        void access() {
            expose();
            while (splice());
        }

        void evert() {
            access();
            splay();
            rev ^= 1;
        }
    } N[MAXN], E[MAXM], *a[MAXM][2];

    void link(Node *u, Node *v) {
        // printf("Linking %ld as %ld's parent.\n", u - N + 1, v - N + 1);
        v->evert();
        u->expose();
        v->pp = u;
    }

    void link(const int u, const int v, const int i, const int w) {
        E[i].w = w;
        a[i][0] = &N[u];
        a[i][1] = &N[v];
        link(&N[u], &E[i]);
        link(&E[i], &N[v]);
    }

    void cut(Node *u, Node *v) {
        v->evert();
        v->expose();
        u->splay();
        u->pp = NULL;
    }

    void cut(const int i) {
        cut(a[i][0], &E[i]);
        cut(&E[i], a[i][1]);
    }

    Node *find(const int u) {
        Node *v = &N[u];
        v->access();
        v->splay();
        if (!v->c[0]) {
            // printf("find(%d) = %ld\n", u + 1, v - N + 1);
            return v;
        }
        while (v->c[0]) v = v->c[0];
        // printf("find(%d) = %ld\n", u + 1, v - N + 1);
        return v;
    }

    bool test(const int u, const int v) {
        return find(u) == find(v);
    }

    int queryMax(const int u, const int v) {
        N[u].evert();
        N[v].access();
        N[v].splay();
        assert(N[v].max >= E);
        return N[v].max - E;
    }
} lct;

struct Edge {
    int u, v, a, b;

    bool operator<(const Edge &other) const { return a < other.a; }
} E[MAXM];

int main() {
    freopen("test.in", "r", stdin);
    freopen("test.ans", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) scanf("%d %d %d %d", &E[i].u, &E[i].v, &E[i].a, &E[i].b), E[i].u--, E[i].v--;
    std::sort(E, E + m);

    int ans = INT_MAX;
    for (int i = 0; i < m; i++) {
        Edge &e = E[i];
        if (e.u == e.v) continue;
        if (lct.test(e.u, e.v)) {
            // printf("[%d, %d, %d, %d] will lead to a circle!\n", e.u + 1, e.v + 1, e.a, e.b);
            int max = lct.queryMax(e.u, e.v);
            // printf("max = %d\n", max);
            if (E[max].b > e.b) {
                lct.cut(max);
                lct.link(e.u, e.v, i, e.b);
            }
        } else {
            // printf("Connecting [%d, %d, %d, %d] ...\n", e.u + 1, e.v + 1, e.a, e.b);
            lct.link(e.u, e.v, i, e.b);
        }

        if (lct.test(0, n - 1)) ans = std::min(ans, e.a + E[lct.queryMax(0, n - 1)].b);
    }

    printf("%d\n", ans == INT_MAX ? -1 : ans);

    return 0;
}