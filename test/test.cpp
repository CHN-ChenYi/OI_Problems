/*
Name: string(LJOJ4517)
Author: godwings
Date: 16/09/2017
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
const int kMaxN = 500010;
typedef long long LL;
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
    inline void scan(char &x) {
        while (!isalpha(x = getchar()) && x != '?') { }
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

int n, m;
char s[kMaxN];

LL k, left_k;
int same[kMaxN], top;

class Splay {
private:
    struct Node {
        int key, size;
        bool reverse;
        Node *left, *right, *father;
        Node(Node *new_fa, const int new_key) {
            size = 1;
            reverse = 0;
            key = new_key;
            father = new_fa;
            left = right = NULL;
        }
        void Maintain() {
            size = 1;
            if (left != NULL)
                size += left->size;
            if (right != NULL)
                size += right->size;
        }
        void PushDown() {
            if (reverse) {
                reverse = 0;
                swap(left, right);
                if (left != NULL)
                    left->reverse ^= 1;
                if (right != NULL)
                    right->reverse ^= 1;
            }
        }
    }*root;
    void Zig(Node *now) {
        Node *fa = now->father;
        if (fa->father != NULL) {
            if (fa->father->left == fa)
                fa->father->left = now;
            else
                fa->father->right = now;
        }
        now->father = fa->father;
        fa->left = now->right;
        if (fa->left != NULL)
            fa->left->father = fa;
        now->right = fa;
        fa->father = now;
        fa->Maintain();
        now->Maintain();
    }
    void Zag(Node *now) {
        Node *fa = now->father;
        if (fa->father != NULL) {
            if (fa->father->left == fa)
                fa->father->left = now;
            else
                fa->father->right = now;
        }
        now->father = fa->father;
        fa->right = now->left;
        if (fa->right != NULL)
            fa->right->father = fa;
        now->left = fa;
        fa->father = now;
        fa->Maintain();
        now->Maintain();
    }
    void splay(Node *now, Node *dst_fa) {
        Node *nxt;
        while (now->father != dst_fa) {
            nxt = now->father;
            nxt->PushDown();
            now->PushDown();
            if (nxt->father == dst_fa) {
                if (nxt->left == now)
                    Zig(now);
                else
                    Zag(now);
            } else {
                if (nxt == nxt->father->left) {
                    if (now == nxt->left) {
                        Zig(nxt);
                        Zig(now);
                    } else {
                        Zag(now);
                        Zig(now);
                    }
                } else {
                    if (now == nxt->right) {
                        Zag(nxt);
                        Zag(now);
                    } else {
                        Zig(now);
                        Zag(now);
                    }
                }
            }
        }
        if (dst_fa == NULL)
            root = now;
    }
    Node* Insert(Node *&now, Node *fa, const int &key) {
        if (now == NULL) {
            now = new Node(fa, key);
            return now;
        }
        return Insert(now->right, now, key);
    }
    Node* GetKth(Node *&now, int now_k, const int &k) {
        if (k < now_k) {
            now->left->PushDown();
            return GetKth(now->left, now_k - 1 - (now->left->right != NULL ? now->left->right->size : 0), k);
        } else {
            if (k - now_k < 1) {
                return now;
            } else {
                now->right->PushDown();
                return GetKth(now->right, now_k + 1 + (now->right->left != NULL ? now->right->left->size : 0), k);
            }
        }
    }
    void Print(Node *now) {
        now->PushDown();
        if (now->left != NULL)
            Print(now->left);
        if (now->key != -1)
            same[++top] = now->key;
        if (now->right != NULL)
            Print(now->right);
    }
    void TreePrint(Node* now, int depth) {
        if (now == NULL)
            return;
        TreePrint(now->right, depth + 1);
        for (int i = 0; i < depth; i++) {
            printf("   ");
        }
        printf("%d(reverse:%d\tsize:%d)(%p)\n", now->key, now->reverse, now->size, now);
        TreePrint(now->left, depth + 1);
    }

public:
    void Insert(int x) {
        Node *now = Insert(root, NULL, x);
        splay(now, NULL);
    }
    void Reverse(int l, int r) {
        root->PushDown();
        Node *now = GetKth(root, root->left != NULL ? root->left->size + 1 : 1, r);
        splay(now, NULL);
        root->PushDown();
        now = GetKth(root, root->left != NULL ? root->left->size + 1 : 1, l);
        splay(now, root);
        root->left->right->reverse ^= 1;
    }
    void Print() {
        Print(root);
    }
    void TreePrint() {
        printf("\n/-----------------------------------\\\n");
        TreePrint(root, 0);
        printf("\\-----------------------------------/\n\n");
    }
}splay;

int cnt[kMaxN], now_cnt;
LL Pow(LL x, LL n) {
    LL ret = 1;
    while (n) {
        if (n & 1) ret = ret * x;
        x = x * x;
        n >>= 1;
    }
    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
    freopen("test.in", "r", stdin);
#else
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif
    scan(n, m);
    scan(k);
    splay.Insert(-1);
    for (int i = 1; i <= n; i++) {
        scan(s[i]);
        splay.Insert(i);
    }
    splay.Insert(-1);
    for (int i = 1, l, r; i <= m; i++) {
        scan(l, r);
        splay.Reverse(l, r + 2);
    }
    splay.Print();
    for (int i = n; i; i--) {
        if (s[i] != '?')
            continue;
        if (s[same[i]] != '?')
            s[i] = s[same[i]];
        if (same[i] < i)
            continue;
        else
            cnt[i] = (now_cnt == 13 ? 13 : now_cnt++);
    }
    left_k = k - 1;
    for (int i = 1; i <= n; i++) {
        if (s[i] != '?' || same[i] < i)
            continue;
        const LL p = Pow(26, cnt[i]);
        s[i] = left_k / p + 'a';
        left_k %= p;
    }
    for (int i = 1; i <= n; i++)
        printf("%c", s[i] != '?' ? s[i] : s[same[i]]);
    return 0;
}
