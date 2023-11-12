#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n, m, k;
  std::cin>>n>>m>>k;
  vec<vec<ll>> mat(n + 1, vec<ll>(m + 1, 0));

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      int t;
      std::cin>>t;
      mat[i][j] = mat[i - 1][j] + mat[i][j - 1] - mat[i - 1][j - 1] + t;
    }
  }

  ll max = 0;
  for(int i = k; i <= n; i++) {
    for(int j = k; j <= m; j++) {
      max = std::max(max, mat[i][j] - mat[i - k][j] - mat[i][j - k] + mat[i - k][j - k]);
    }
  }
  std::cout<<max;

  std::cout.flush();
}
