/* URL: https://blog.sengxian.com/algorithms/suffix-array */
#include <cstdio>
#include <cstring>

static const int maxNode = 100000 + 3;
int sa[maxNode], rank[maxNode], n;
char str[maxNode];
void buildSA(int m) {
  static int cnt[maxNode], tmpSA[maxNode], rank1[maxNode], rank2[maxNode];
  n = strlen(str) + 1; str[n] = 0; //½áÎ²µÄ $
  fill(cnt, cnt + m, 0);
  for (int i = 0; i < n; ++i) cnt[(int)str[i]]++;
  for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
  for (int i = 0; i < n; ++i) rank[i] = cnt[(int)str[i]] - 1;
  for (int l = 1; l < n; l <<= 1) {
    for (int i = 0; i < n; ++i)
      rank1[i] = rank[i], rank2[i] = i + l < n ? rank1[i + l] : 0;
    fill(cnt, cnt + n, 0);
    for (int i = 0; i < n; ++i) cnt[rank2[i]]++;
    for (int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; --i) tmpSA[--cnt[rank2[i]]] = i;
    fill(cnt, cnt + n, 0);
    for (int i = 0; i < n; ++i) cnt[rank1[i]]++;
    for (int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; --i) sa[--cnt[rank1[tmpSA[i]]]] = tmpSA[i];
    bool unique = true;
    rank[sa[0]] = 0;
    for (int i = 1; i < n; ++i) {
      rank[sa[i]] = rank[sa[i - 1]];
      if (rank1[sa[i]] == rank1[sa[i - 1]] && rank2[sa[i]] == rank2[sa[i - 1]]) unique = false;
      else rank[sa[i]]++;
    }
    if (unique) break;
  }
}


int main() {

  return 0;
}