#include <algorithm>
#include <bits/stdc++.h>
#include <limits.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

vec<int> b; //banknoty (nominaly)
vec<int> c; //ilosc

void print_mat(vec<vec<int>>& mat) {
  for (auto row : mat) {
    for (auto c : row) {
      std::cout<<c<<" ";
    }
    std::cout<<"\n";
  }
}

void solve(int k) {
  vec<vec<int>> solves(b.size() + 1, vec<int>(k + 1, INT_MAX - 100));
  
  for (int i = 0; i < solves.size(); i++) {
    for (int j = 0; j < solves[0].size(); j++) {
      if (i == 0 || j == 0) {
        solves[i][j] = 0;
        continue;
      }
      if(solves[i - 1][j] != 0) {
        solves[i][j] = solves[i - 1][j];
      }
      for(int count = 1; (count <= c[i - 1] && (j - b[i - 1]*count) >= 0); count++) {
        if(solves[i - 1][j - b[i - 1] * count] == 0 && i != 1) {
          continue;
        }
        solves[i][j] = std::min(solves[i][j], solves[i - 1][j - b[i - 1] * count] + count); 
      }
    }
  }
  print_mat(solves);
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
    c.push_back(t_c);
  }

  int k;
  std::cin>>k;  
  solve(k); 
  
  std::cout.flush();
}
