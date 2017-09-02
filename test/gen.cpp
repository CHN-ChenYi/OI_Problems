#include <bits/stdc++.h>

const int T = 20;
const int N = 10000;
const int M = 10000;
const int W = 1000000;

int main() {
    freopen("test.in", "w", stdout);
    srand(time(NULL));
    printf("%d\n", T);
    for (int t = 1; t <= T; t++) {
        printf("%d\n", N);
        for (int i = 2; i <= N; i++)
            printf("%d %d %d\n", i, rand() % (i - 1) + 1, rand() * rand() % W);
        for (int i = 1; i <= M; i++) {
            const int opt = rand() % 2;
            if (opt) {
                const int x = rand() % N + 1;
                int y = rand() % N + 1;
                while (x == y)
                    y = rand() % N + 1;
                printf("QUERY %d %d\n", x, y);
            } else {
                printf("CHANGE %d %d\n", rand() % (N - 1) + 1, rand() * rand() % W);
            }
        }
        puts("DONE");
    }
    return 0;
}
