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

  mat[0][1] = 1;
  for (ll i = 1; i <= n; i++) {
    for (ll j = 1; j <= n; j++) {
      ll t;
      std::cin>>t;
      if (t == 1) {
        mat[i][j] = 0;
      } else {
        mat[i][j] = (mat[i - 1][j] + mat[i][j - 1]) % MOD;
      }
    }
  }

  /*
  for (auto row : mat) {
    for (auto c : row) {
      std::cout<<c<<" ";
    }
    std::cout<<"\n";
  }
  */
  std::cout<<mat[n][n];

  std::cout.flush();
}
