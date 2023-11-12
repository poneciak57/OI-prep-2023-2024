#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const ll MOD = 1000000007;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n;
  std::cin>>n;

  vec<vec<ll>> mat(n + 1, vec<ll>(n + 1, 0));
  vec<vec<ll>> mat2(n + 1, vec<ll>(n + 1, 0));
  
  mat2[0][1] = 1;

  for (ll i = 1; i <= n; i++) {
    for (ll j = 1; j <= n; j++) {
      ll t;
      std::cin>>t;
      if(mat[i - 1][j] == mat[i][j - 1]) {
        mat[i][j] = mat[i - 1][j] + t;
        mat2[i][j] = (mat2[i - 1][j] + mat2[i][j - 1]) % MOD;
      } else if(mat[i - 1][j] > mat[i][j - 1]) {
        mat[i][j] = mat[i - 1][j] + t;
        mat2[i][j] = mat2[i - 1][j];
      } else {
        mat[i][j] = mat[i][j - 1] + t;
        mat2[i][j] = mat2[i][j - 1];
      }
    }
  }

  std::cout<<mat2[n][n];

  std::cout.flush();
}
