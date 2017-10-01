#include <cstdio>
#include <vector>
typedef std::pair<double, double> pair;
typedef std::vector <pair> vector;
using std::max;
vector len[1 << 7];
int a[7];
int weight[1 << 7];
double w;
void dfs(vector &len_s, const int l, const int r, const int s) {
    if (s == 0) {
        if (l != 0 && r != 0) {
            const vector &ll = len[l], rr = len[r];
            const int w_l = weight[l], w_r = weight[r];
            const double l_l = double(w_r) / (w_l + w_r),
                l_r = double(w_l) / (w_l + w_r);
            for (int i = ll.size() - 1; i >= 0; --i) {
                const double len_l = ll[i].first, len_r = ll[i].second;
                for (int j = rr.size() - 1; j >= 0; --j) {
                    const pair tmp(max(len_l + l_l, rr[j].first - l_r),
                                   max(len_r - l_l, rr[j].second + l_r));
                    if (tmp.first + tmp.second <= w)
                        len_s.push_back(tmp);
                }
            }
        }
    } else {
        dfs(len_s, l | (s & -s), r, s ^ (s & -s));
        dfs(len_s, l, r | (s & -s), s ^ (s & -s));
    }
}
int main() {
    freopen("economic.in", "r", stdin);
    freopen("economic.out", "w", stdout);
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%lf", &w);
        int n;
        scanf("%d", &n);
        const int max = (1 << n) - 1;
        for (int i = 0; i < n; ++i)
            scanf("%d", a + i);
        if (w < 0) {
            puts("-1");
            continue;
        }
        for (int s = max; s >= 0; --s)
            len[s].clear();
        for (int i = 0; i < n; ++i) {
            len[1 << i].push_back(pair(0, 0));
            weight[1 << i] = a[i];
        }
        for (int s = 3; s <= max; ++s)
            if ((s & -s) != s) {
                dfs(len[s], 0, 0, s);
                weight[s] = weight[s & -s] + weight[s ^ (s & -s)];
            }
        const vector &tmp = len[max];
        if (tmp.size() == 0)
            puts("-1");
        else {
            double ans = -1;
            for (int i = tmp.size() - 1; i >= 0; --i)
                ans = ::max(ans, tmp[i].first + tmp[i].second);
            printf("%.10lf\n", ans);
        }
    }
    return 0;
}
