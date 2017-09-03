#include <bits/stdc++.h>

inline int rand(const int lim) {
    return rand() * rand() % lim + 1;
}

const int T = 20;
const int N = 10000;
const int M = 10000;

int t, n, m;

int main() {
    freopen("test.in", "w", stdout);
    srand(time(NULL));
    t = rand(T);
    n = rand(N);
    m = rand(M);
    printf("%d\n", t);
    printf("%d %d\n", n, m);
    return 0;
}
