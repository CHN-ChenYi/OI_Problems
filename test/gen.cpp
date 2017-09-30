#include <ctime>
#include <cstdio>
#include <cstdlib>

inline int rand(const int lim) {
    return rand() * rand() % lim + 1;
}

const int T = 15;
const int N = 100000;
const int M = 100000;

int t, n, m;

int main() {
    freopen("test.in", "w", stdout);
    srand(time(NULL));
    t = rand(T);
    printf("%d\n", t);
    while (t--) {
        n = rand(N);
        printf("%d\n", n);
        for (int i = 1; i <= n; i++)
            printf("%d %d %d\n", rand(M), rand(M), rand(M));
    }
    return 0;
}
