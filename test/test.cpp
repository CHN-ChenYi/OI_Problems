/*
Name: [ZJOI2008]count(BZOJ1036)
Author: godwings
Date: 03/09/2017
*/
#include <cctype>
#include <cstdio>
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

template<typename T>
struct LinkCutTree {
    enum Relation {
        L, R
    };
    struct Node {
        bool reversed;
        T sum, value, max_val;
        typedef Node* ptrNode;
        ptrNode child[2], parent, path_parent;
        Node() {
            reversed = false;
            child[L] = child[R] = parent = path_parent = NULL;
        }
        explicit Node(const T value_) {
            reversed = false;
            sum = value = max_val = value_;
            child[L] = child[R] = parent = path_parent = NULL;
        }
        Relation GetRelation() {
            return this == parent->child[L] ? L : R;
        }
        void Maintain() {
            sum = max_val = value;
            if (child[L]) {
                sum += child[L]->value;
                max_val = max(max_val, child[L]->max_val);
            }
            if (child[R]) {
                sum += child[R]->value;
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
            const Relation now = GetRelation();
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
                child[R].path_parent = parent;
                child[R].parent = this;
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
            path_parent->Maintain();
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
    };
    Node *node[kMaxN];
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

    return 0;
}
