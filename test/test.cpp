/*
Name: [NOI2014]magicalforest(BZOJ3669)
Author: godwings
Date: 06/09/2017
*/
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>
using std::max;
using std::min;
using std::swap;
using std::sort;
const int kMaxN = 50000;
const int kMaxM = 100000;

namespace FastIO {
    template <class T>
    inline void scan(T &x) {
        bool positive = 1;
        char c;
        while (isdigit(c = getchar()) == 0) {
            if (!positive) positive = 1;
            if (c == '-') positive = 0;
        }
        x = 0;
        for (; isdigit(c) != 0; c = getchar())
            x = x * 10 + (c & 0xf);
        if (!positive)
            x *= -1;
    }
    template <class T>
    inline void scan(T &x, T &y) {
        scan(x); scan(y);
    }
    template <class T>
    inline void scan(T &x, T &y, T &z) {
        scan(x); scan(y); scan(z);
    }
}  // namespace FastIO
using FastIO::scan;

template<typename T>
struct LinkCutTree {
 private:
    enum Relation {
        L, R
    };
    struct Node {
        bool reversed;
        T value, max_val;
        typedef Node* ptrNode;
        ptrNode child[2], parent, path_parent;
        Node() {
            value = max_val;
            child[L] = child[R] = parent = path_parent = NULL;
        }
        Node(const int value_) {
            value = max_val = value_;
            child[L] = child[R] = parent = path_parent = NULL;
        }
        Relation GetRelation() {
            return this == parent->child[L] ? L : R;
        }
        void Maintain() {
            max_val = value;
            if (child[L])
                max_val = max(max_val, child[L]->max_val);
            if (child[R])
                max_val = max(max_val, child[R]->max_val);
        }
        void PushDown() {
            if (reversed) {
                swap(child[L], child[R]);
                if (child[L])
                    child[L]->reversed ^= 1;
                if (child[R])
                    child[R]->reversed ^= 1;
                reversed = false;
            }
        }
        void Rotate() {
            swap(path_parent, parent->path_parent);
            const ptrNode OldParent = parent;
            const Relation now = GetRelation();
            if (OldParent->parent)
                OldParent->parent->child[OldParent->GetRelation()] = this;
            parent = OldParent->parent;
            OldParent->parent = this;
            OldParent->child[now] = child[now ^ 1];
            if (child[now ^ 1])
                child[now ^ 1]->parent = OldParent;
            OldParent->parent = this;
            child[now ^ 1] = OldParent;
            OldParent->Maintain();
            Maintain();
        }
        void Splay() {
            while (parent) {
                if (!parent->parent) {
                    parent->PushDown();
                    Rotate();
                } else {
                    parent->parent->PushDown();
                    parent->PushDown();
                    if (GetRelation() == parent->GetRelation()) {
                        parent->Rotate();
                        Rotate();
                    } else {
                        Rotate();
                        Rotate();
                    }
                }
            }
        }
        void Expose() {
            Splay();
            PushDown();
            if (child[R]) {
                child[R]->parent = NULL;
                child[R]->path_parent = this;
                child[R] = NULL;
                Maintain();
            }
        }
        void Splice() {
            Splay();
            if (!path_parent)
                return false;
            path_parent->Expose();
            path_parent->child[R] = this;
            parent = path_parent;
            path_parent = NULL;
            parent->Maintain();
            return true;
        }
        void Access() {
            Expose();
            while (Splice()) { }
        }
        void MakeRoot() {
            Access();
            Splay();
            reversed ^= 1;
        }
    };
    void Link(Node *u, Node *v) {
        v->MakeRoot();
        v->path_parent = u;
    }
    void Cut(Node *u, Node *v) {
        u->MakeRoot();
        v->Access();
        v->Splay();
        v->PushDown();
        v->child[L]->parent = NULL;
        v->child[L] = NULL;
        v->Maintain();
    }
    Node *GetRoot(const int u) {

    }

 public:

};

int n, m;
struct Edge {
    int u, v, a, b;
    bool operator<(const Edge rhs) const {
        return a < rhs.a;
    }
}e[kMaxM];
LinkCutTree<int> LCT;

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(n, m);
    for (int i = 0; i < m; i++) {
        scan(e[i].u, e[i].v);
        scan(e[i].a, e[i].b);
        e[i].u--;
        e[i].v--;
    }
    sort(e, e + m);
    int ans = INT_MAX;
    for (int i = 0; i < m; i++) {
        Edge &now = e[i];
        if (now.u == now.v)
            continue;
        if (LCT.Find(now.u, now.v)) {
            const int max_val = LCT.GetMax(now.u, now.v);
            if (e[max_val].b > now.b) {
                LCT.Cut(max_val);
                LCT.Link(now.u, now.v, i, now.b);
            }
        } else {
            LCT.Link(now.u, now.v, i, now.b);
        }
        if (LCT.Find(0, n - 1))
            ans = min(ans, now.a + e[LCT.GetMax(0, n - 1)].b);
    }
    printf("%d\n", ans == INT_MAX ? -1 : ans);
    return 0;
}
