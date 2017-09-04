#include <bits/stdc++.h>

const int MAXN = 10000;
const int MAXM = 200000;

struct LinkCutTree {
    enum Relation {
        L = 0, R = 1
    };

    struct Node {
        Node *child[2], *parent, *pathParent;
        bool reversed;

        Node() : parent(NULL), pathParent(NULL), reversed(false) {
            child[0] = child[1] = NULL;
        }

        Relation relation() {
            return this == parent->child[L] ? L : R;
        }

        void pushDown() {
            if (reversed) {
                std::swap(child[L], child[R]);
                if (child[L]) child[L]->reversed ^= 1;
                if (child[R]) child[R]->reversed ^= 1;
                reversed = false;
            }
        }

        void rotate() {
            if (parent->parent) parent->parent->pushDown();
            parent->pushDown(), pushDown();

            Node *oldParent = parent;
            Relation r = relation();

            if (oldParent->parent) oldParent->parent->child[oldParent->relation()] = this;
            parent = oldParent->parent;

            if (child[r ^ 1]) child[r ^ 1]->parent = oldParent;
            oldParent->child[r] = child[r ^ 1];

            oldParent->parent = this;
            child[r ^ 1] = oldParent;

            std::swap(pathParent, oldParent->pathParent);
        }

        void splay() {
            while (parent != NULL) {
                if (parent->parent) parent->parent->pushDown();
                parent->pushDown(), pushDown();

                if (parent->parent == NULL) rotate();
                else if (parent->relation() == relation()) parent->rotate(), rotate();
                else rotate(), rotate();
            }
            pushDown();
        }

        void expose() {
            splay();
            if (child[R]) {
                std::swap(child[R]->pathParent, child[R]->parent);
                child[R] = NULL;
            }
        }

        bool splice() {
            splay();
            if (!pathParent) return false;
            pathParent->expose();
            pathParent->child[R] = this;
            std::swap(parent, pathParent);
            return true;
        }

        void access() {
            expose();
            while (splice());
        }

        Node *findRoot() {
            access();
            splay();
            Node *v = this;
            while (v->pushDown(), v->child[L]) v = v->child[L];
            return v;
        }

        void evert() {
            access();
            splay();
            reversed ^= 1;
        }
    } nodes[MAXN];

    void link(int u, int v) {
        nodes[v - 1].evert();
        nodes[v - 1].pathParent = &nodes[u - 1];
    }

    void cut(int u, int v) {
        nodes[u - 1].evert();
        nodes[v - 1].access();
        nodes[u - 1].splay();
        nodes[u - 1].child[R] = NULL;
        nodes[v - 1].parent = NULL;
    }

    Node *find(int u) {
        return nodes[u - 1].findRoot();
    }
} lct;

inline int rand(const int lim) {
    return rand() * rand() % lim + 1;
}

const int N = 100;
const int M = 100;

int n, m;
const char ope[3][10] = {"Query\t", "Connect\t", "Destroy\t"};

int main() {
    freopen("test.in", "w", stdout);
    srand(time(NULL));
    n = rand(N);
    m = rand(M);
    printf("%d %d\n", n, m);
    for (int i = 1, opt, u, v; i <= m; i++) {
        opt = rand(3);
        u = rand(n);
        v = rand(n);
        switch (opt) {
            case 0:
                while (u == v)
                    v = rand(n);
                printf("%s%d\t%d\n", ope[opt], u, v);
                break;
            case 1:
                while (lct.find(u) == lct.find(v)) {
                    u = rand(n);
                    v = rand(n);
                }
                printf("%s%d\t%d\n", ope[opt], u, v);
                lct.link(u, v);
                break;
            case 2:
                while (lct.find(u) != lct.find(v)) {
                    u = rand(n);
                    v = rand(n);
                }
                printf("%s%d\t%d\n", ope[opt], u, v);
                lct.cut(u, v);
                break;
        }
    }
    return 0;
}
