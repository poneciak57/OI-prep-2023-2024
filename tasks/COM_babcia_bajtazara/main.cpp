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

  for (ll x = 1; x < solves.size(); x++) 
  {
    for (ll y = 1; y < solves[0].size(); y++)
    {
      ll max_prev = std::max(solves[x - 1][y], solves[x][y - 1]);
      if(a[x - 1] == b[y - 1]) {
        solves[x][y] = solves[x - 1][y - 1] + 1;
      } else {
        solves[x][y] = max_prev;
      }
    }
  }

  ll x = a.length();
  ll y = b.length();

  ll index = solves[x][y];
  char ret[index + 1];
  ret[index] = '\0';

  while (x > 0 && y > 0) {
    if (a[x - 1] == b[y - 1]) {
      ret[index - 1] = a[x - 1];
      x--;
      y--;
      index--;
    } else if (solves[x - 1][y] > solves[x][y - 1]) {
      x--;
    } else {
      y--;
    }
  }

  //print_mat(solves);

  std::cout<<solves[a.length()][b.length()]<<"\n";
  std::cout<<ret;
  

  std::cout.flush();
}
