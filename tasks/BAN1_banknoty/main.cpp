#include <algorithm>
#include <bits/stdc++.h>
#include <limits.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

vec<int> b; //banknoty (nominaly)
vec<int> ban;

void print_mat(vec<vec<int>>& mat) {
  for (auto row : mat) {
    for (auto c : row) {
      std::cout<<c<<" ";
    }
    std::cout<<"\n";
  }
}

void solve(int k) {
  vec<vec<int>> solves(ban.size() + 1, vec<int>(k + 1, -1));
  solves[0][0] = 0;
  for (int i = 1; i < solves.size(); i++) {
    for (int j = 0; j < solves[0].size(); j++) {
      if(j == 0) {
        solves[i][j] = 0;
      }
      if(j-ban[i] >= 0 && solves[i - 1][j - ban[i]] != -1) {
        if(solves[i - 1][j] != -1) {
          solves[i][j] = std::min(solves[i - 1][j], solves[i - 1][j - ban[i]] + 1);
        } else {
          solves[i][j] = solves[i - 1][j - ban[i]] + 1;
        }
      } else {
        solves[i][j] = solves[i - 1][j];
      }
    }
  }
  std::cout<<solves[ban.size()][k];
  //print_mat(solves);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n;
  std::cin>>n;

  for (int i = 0; i < n; i++) {
    int t_b;
    std::cin>>t_b;
    b.push_back(t_b);
  }

  for (int i = 0; i < n; i++) {
    int t_c;
    std::cin>>t_c;
    while (t_c--) {
      ban.push_back(b[i]);
    }
  }

  int k;
  std::cin>>k;  
  solve(k); 
  
  std::cout.flush();
}
