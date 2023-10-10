#include <algorithm>
#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

void print_mat(vec<vec<ll>>& mat) {
  for (auto row : mat) {
    for (auto c : row) {
      std::cout<<c<<" ";
    }
    std::cout<<"\n";
  }
}

// Dopisac trzymanie tego najdluzszego ciagu
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  str a, b;
  std::cin>>a>>b;

  vec<vec<ll>> solves(a.length() + 1, vec<ll>(b.length() + 1, 0));

  ll last_add = 0;
  str ret = "";
  for (ll x = 1; x < solves.size(); x++) 
  {
    for (ll y = 1; y < solves[0].size(); y++)
    {
      ll max_prev = std::max(solves[x - 1][y], solves[x][y - 1]);
      ll with_cur = solves[x - 1][y - 1] + (a[x - 1] == b[y - 1]);
      if(with_cur > max_prev) {
        solves[x][y] = with_cur;
        if(y > last_add) {
          ret += a[x - 1];
        } else {
          ret = a[x - 1];
        }
        last_add = y;
      } else {
        solves[x][y] = max_prev;
      }
    }
  }
  
  //print_mat(solves);

  std::cout<<solves[a.length()][b.length()]<<"\n";
  std::cout<<ret;
  

  std::cout.flush();
}
