/*
Name:  [ZJOI2008]count(BZOJ1036)
Author: godwings
Date: 02/09/2017
*/
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int kMaxN = 30000;
using std::max;
using std::swap;

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

template <typename T>
struct LinkCutTree {
    enum Relation {
        L, R
    };
    struct Node {
        bool reversed;
        T value, sum, max_val;
        typedef Node* ptrNode;
        ptrNode child[2], parent, path_parent;
        Node() {
            reversed = false;
            child[L] = child[R] = parent = path_parent = NULL;
        }
        explicit Node(const T value_) {
            reversed = false;
            value = sum = max_val = value_;
            child[L] = child[R] = parent = path_parent = NULL;
        }
        Relation GetRelation() {
            return this == parent->child[L] ? L : R;
        }
        void Maintain() {
            sum = max_val = value;
            if (child[L]) {
                sum += child[L]->sum;
                max_val = max(max_val, child[L]->max_val);
            }
            if (child[R]) {
                sum += child[R]->sum;
                max_val = max(max_val, child[R]->max_val);
            }
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
            PushDown();
            swap(path_parent, parent->path_parent);
            Relation now = GetRelation();
            ptrNode OldParent = parent;
            if (OldParent->parent)
                OldParent->parent->child[OldParent->GetRelation()] = this;
            parent = OldParent->parent;
            OldParent->child[now] = child[now ^ 1];
            if (child[now ^ 1])
                child[now ^ 1]->parent = OldParent;
            child[now ^ 1] = OldParent;
            OldParent->parent = this;
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
        bool Splice() {
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
        const T &GetSum() {
            Access();
            Splay();
            return sum;
        }
        const T &GetMax() {
            Access();
            Splay();
            return max_val;
        }
    }*node[kMaxN];
    void MakeTree(const int u, const T value) {
        node[u - 1] = new Node(value);
    }
    void Link(const int u, const int v) {
        node[v - 1]->MakeRoot();
        node[v - 1]->path_parent = node[u - 1];
    }
    void Cut(const int u, const int v) {
        const int u_id = u - 1;
        const int v_id = v - 1;
        node[u_id]->MakeRoot();
        node[v_id]->Access();
        node[v_id]->Splay();
        node[v_id]->PushDown();
        node[v_id]->child[L]->parent = NULL;
        node[v_id]->child[L] = NULL;
        node[v_id]->Maintain();
    }
    void Modify(const int u, const T value) {
        const int u_id = u - 1;
        node[u_id]->Splay();
        node[u_id]->value = value;
        node[u_id]->Maintain();
    }
    T GetSum(const int u, const int v) {
        node[u - 1]->MakeRoot();
        return node[v - 1]->GetSum();
    }
    T GetMax(const int u, const int v) {
        node[u - 1]->MakeRoot();
        return node[v - 1]->GetMax();
    }
};
struct Int {
    int num;
    Int() {
        num = 0;
    }
    Int(const int num_) {
        num = num_;
    }
    bool operator<(const Int rhs) const {
        return num < rhs.num;
    }
    Int operator+=(const Int rhs) {
        num += rhs.num;
        return *this;
    }
    inline void print_endl() {
        printf("%d\n", num);
    }
};

struct UndirectedEdge {
    int u, v;
    UndirectedEdge() {
        u = v = 0;
    }
    UndirectedEdge(const int u_, const int v_) {
        u = u_;
        v = v_;
    }
}edge[kMaxN];

int n, q;
char str[10];
LinkCutTree<Int> LCT;

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(n);
    for (int i = 0, u, v; i < n - 1; i++) {
        scan(u, v);
        edge[i] = UndirectedEdge(u, v);
    }
    for (int i = 1, v; i <= n; i++) {
        scan(v);
        LCT.MakeTree(i, v);
    }
    for (int i = 0; i < n - 1; i++)
        LCT.Link(edge[i].u, edge[i].v);
    scan(q);
    for (int i = 0, u, v, t; i < q; i++) {
        scanf("%s", str);
        if (str[1] == 'H') {
            scan(u, t);
            LCT.Modify(u, t);
        } else if (str[1] == 'M') {
            scan(u, v);
            LCT.GetMax(u, v).print_endl();
        } else if (str[1] == 'S') {
            scan(u, v);
            LCT.GetSum(u, v).print_endl();
        }
    }
    return 0;
}
