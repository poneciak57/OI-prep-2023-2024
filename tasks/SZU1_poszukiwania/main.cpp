#include <algorithm>
#include <bits/stdc++.h>
#include <limits.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

void reverse(str s)
{
    for (int i = s.length() - 1; i >= 0; i--)
        std::cout << s[i];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n;
  std::cin>>n;

  vec<vec<ll>> mat(n + 1, vec<ll>(n + 1, 0));
  for (ll i = 1; i <= n; i++) {
    for (ll j = 1; j <= n; j++) {
      ll t;
      std::cin>>t;
      mat[i][j] = std::max(mat[i - 1][j] + t, mat[i][j - 1] + t);
    }
  }

  ll x = n, y = n;
  str ret = "";
  while(x != 1 || y != 1) {
    if(mat[x][y - 1] >= mat[x - 1][y]) {
      y--;
      ret += "P";
    } else {
      x--;
      ret += "D";
    }
  }
  //std::cout<<mat[n][n];
  reverse(ret);

  std::cout.flush();
}
