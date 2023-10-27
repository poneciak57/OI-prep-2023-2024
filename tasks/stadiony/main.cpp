#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

vec<vec<int>> mat;

void print_mat() {
  for (auto r : mat) {
    for(auto v: r) {
      std::cout<<v<<" ";
    }
    std::cout<<"\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n, m, d;
  std::cin>>n>>m;

  mat = vec<vec<int>>(m, vec<int>(n, 1));

  std::cin>>d;
  while(d--) {
    int tx, ty;
    std::cin>>tx>>ty;
    mat[ty - 1][tx - 1] = 0;
  }

  int max = 0;

  for(int i = 1; i < m; i++) {
    for(int j = 1; j < n; j++) {
      if(mat[i][j] != 0) {
        mat[i][j] = std::min(mat[i - 1][j -1], std::min(mat[i - 1][j], mat[i][j - 1])) + 1;
      }
      max = std::max(mat[i][j], max);
    }
  }

  //print_mat();
  std::cout<<max*max;

  std::cout.flush();
}
