/*
Name: SA(LJOJ3313)
Author: godwings
Date: 08/11/2017
*/
#include <cmath>
#include <cstdio>
#include <cstring>

#include <cctype>
namespace FastIO {
  char c;
  bool positive;
  template <class T_1>
  inline void scan(T_1 &x) {
    x = 0;
    positive = 1;
    while (!isdigit(c = getchar())) {
      if (!positive) positive = 1;
      if (c == '-') positive = 0;
    }
    while (isdigit(c)) {
      x = x * 10 + (c & 0xf);
      c = getchar();
    }
    if (!positive)
      x *= -1;
  }
  inline void scan(char &x) {
    while (!isgraph(x = getchar())) { }
  }
  inline void scan(double &x) {
    x = 0;
    positive = 1;
    while (!isdigit(c = getchar())) {
      if (!positive) positive = 1;
      if (c == '-') positive = 0;
    }
    while (isdigit(c)) {
      x = x * 10 + (c & 0xf);
      c = getchar();
    }
    if (c == '.') {
      double now = 0.1;
      c = getchar();
      while (isdigit(c)) {
        x += now * (c & 0xf);
        now *= 0.1;
        c = getchar();
      }
    }
    if (!positive)
      x *= -1;
  }
  template <class T_1, class T_2>
  inline void scan(T_1 &a, T_2 &b) {
    scan(a); scan(b);
  }
  template <class T_1, class T_2, class T_3>
  inline void scan(T_1 &a, T_2 &b, T_3 &c) {
    scan(a); scan(b); scan(c);
  }
  template <class T_1, class T_2, class T_3, class T_4>
  inline void scan(T_1 &a, T_2 &b, T_3 &c, T_4 &d) {
    scan(a); scan(b); scan(c); scan(d);
  }
}  // namespace FastIO
using FastIO::scan;

const int kMaxS = 26;
const int kMaxN = 2e5 + 5;

namespace SA {
  int n, bit;
  int s[kMaxN];
  size_t size_of_n_int;
  int sa[kMaxN], height[kMaxN];
  int cnt[kMaxN], rank_1[kMaxN], rank_2[kMaxN], rank[kMaxN];
  void GetSA(char *str) {
    n = strlen(str);
    bit = log2(n);
    size_of_n_int = sizeof(int) * (n + 1);
    for (int i = 0; i < n; i++)
      s[i] = str[i] - 'a';
    for (int i = 0; i < n; i++)
      cnt[s[i]]++;
    for (int i = 1; i <= 26; i++)
      cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++)
      rank_1[i] = cnt[s[i]];
    bool unique = 0;
    for (int bits = 0; !unique && bits <= bit; bits++) {
      const int step = 1 << bits;
      for (int i = n - 1 - step; i >= 0; i--)
        rank_2[i] = rank_1[i + step];
      memset(rank_2 + n - step, 0, sizeof(int) * step);
      memset(cnt, 0, size_of_n_int);
      for (int i = 0; i < n; i++)
        cnt[rank_2[i]]++;
      for (int i = 1; i <= n; i++)
        cnt[i] += cnt[i - 1];
      for (int i = 0; i < n; i++)
        sa[cnt[rank_2[i]]--] = i;
      memset(cnt, 0, size_of_n_int);
      for (int i = 0; i < n; i++)
        cnt[rank_1[i]]++;
      for (int i = 1; i <= n; i++)
        cnt[i] += cnt[i - 1];
      for (int i = n; i; i--)
        rank[sa[i]] = cnt[rank_1[sa[i]]]--;
      for (int i = 0; i < n; i++)
        sa[rank[i]] = i;
      rank[sa[1]] = 1;
      unique = 1;
      for (int i = 2; i <= n; i++) {
        if (rank_1[sa[i]] == rank_1[sa[i - 1]] && rank_2[sa[i]] == rank_2[sa[i - 1]]) {
          unique = 0;
          rank[sa[i]] = rank[sa[i - 1]];
        } else {
          rank[sa[i]] = rank[sa[i - 1]] + 1;
        }
      }
      memcpy(rank_1, rank, size_of_n_int);
    }
    for (int i = 0; i < n; i++)
      sa[rank_1[i]] = i;
  }
  void GetHeight(char *str) {
    GetSA(str);
    int k = 0;
    for (int i = 0; i < n - 1; i++) {
      k -= (k > 0);
      const int j = sa[rank[i] - 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k])
        k++;
      height[rank[i] - 1] = k;
    }
    height[0] = 0;
  }
}  // namespace SA

char s[kMaxN];

int main() {
#ifndef ONLINE_JUDGE
#ifdef _VISUAL_STUDIO
  freopen("test.in", "r", stdin);
#else
  freopen("SA.in", "r", stdin);
  freopen("SA.out", "w", stdout);
#endif  // _VISUAL_STUDIO
#endif  // ONLINE_JUDGE
  scanf("%s", s);
  SA::GetHeight(s);
  for (int i = 1; i <= SA::n; i++)
    printf("%d ", SA::sa[i] + 1);
  putchar('\n');
  for (int i = 0; i < SA::n; i++)
    printf("%d ", SA::height[i]);
  putchar('\n');
  return 0;
}
