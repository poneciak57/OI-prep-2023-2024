#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

void print_mat(vec<vec<int>> &mat) {
  for (auto r : mat) {
    for(auto v : r) {
      std::cout<<v<<" ";
    }
    std::cout<<"\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n, m, q;
  std::cin>>n>>m>>q;

  vec<vec<int>> mat(n + 1, vec<int>(m + 1, 0));

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      char t;
      std::cin>>t;
      mat[i][j] = mat[i - 1][j] + mat[i][j - 1] - mat[i - 1][j - 1] + (t == '#');
    }
  }
  
  while(q--) {
    int x1, x2, y1, y2;
    std::cin>>y1>>x1>>y2>>x2;

    if(mat[x2][y2] - mat[x2][y1 - 1] - mat[x1 - 1][y2] + mat[x1 - 1][y1 - 1]) {
      std::cout<<"NIE\n";
    } else {
      std::cout<<"TAK\n";
    }
  }

  std::cout.flush();
}
