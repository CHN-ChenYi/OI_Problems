/*
Name: [SDOI2008]cave(BZOJ2049)
Author: godwings
Date: 04/09/2017
*/
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int kMaxN = 10000;
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

struct LinkCutTree {
    enum Relation {
        L, R
    };
    struct Node {
        bool reversed;
        typedef Node* ptrNode;
        ptrNode child[2], parent, path_parent;
        Node() {
            child[0] = child[1] = parent = path_parent = NULL;
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
        Relation GetRelation() {
            return this == parent->child[L] ? L : R;
        }
        void Rotate() {
            PushDown();
            swap(path_parent, parent->path_parent);
            const ptrNode OldParent = parent;
            const Relation now = GetRelation();
            if (OldParent->parent)
                OldParent->parent->child[OldParent->GetRelation()] = this;
            parent = OldParent->parent;
            OldParent->child[now] = child[now ^ 1];
            if (child[now ^ 1])
                child[now ^ 1]->parent = OldParent;
            child[now ^ 1] = OldParent;
            OldParent->parent = this;
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
                child[R]->path_parent = this;
                child[R]->parent = NULL;
                child[R] = NULL;
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
        ptrNode GetRoot() {
            Access();
            Splay();
            ptrNode root = this;
            root->PushDown();
            while (root->child[L]) {
                root = root->child[L];
                root->PushDown();
            }
            return root;
        }
    };
    Node *node[kMaxN];
    LinkCutTree() {
        memset(node, 0, sizeof(node));
    }
    void MakeExist(const int u) {
        if (!node[u - 1])
            node[u - 1] = new Node();
    }
    bool CheckExist(const int u) {
        return node[u - 1];
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
    }
    Node* GetRoot(const int u) {
        return node[u - 1]->GetRoot();
    }
}LCT;

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

int n, m;
char ope[10];
const char ans[2][10] = {"No", "Yes"};

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
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%s", ope);
        scan(u, v);
        switch (ope[0]) {
            case 'Q':
                puts(ans[LCT.CheckExist(u) && LCT.CheckExist(v) && LCT.GetRoot(u) == LCT.GetRoot(v)]);
                break;
            case 'C':
                LCT.MakeExist(u);
                LCT.MakeExist(v);
                LCT.Link(u, v);
                break;
            case 'D':
                if (!LCT.CheckExist(u) || !LCT.CheckExist(v))
                    continue;
                LCT.Cut(u, v);
                break;
        }
    }
    return 0;
}
