#include <algorithm>
#include <bits/stdc++.h>
#include <limits.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Banknot {
  int v;
  int c;
};

vec<Banknot> l;

void print_mat(vec<vec<int>>& mat) {
  for (auto row : mat) {
    for (auto c : row) {
      if(c == -1) {
        std::cout<<"- ";
      } else {
        std::cout<<c<<" ";
      }
    }
    std::cout<<"\n";
  }
}

void solve(int k) {
  vec<vec<int>> solves(l.size(), vec<int>(k + 1, -1));
  solves[0][0] = 0;
  for (int i = 1; i < solves.size(); i++) {
    for (int j = 0; j < solves[0].size(); j++) {
      if(j == 0) {
        solves[i][j] = 0;
      }
      int count = 1;
      solves[i][j] = solves[i - 1][j];
      int back_track = j - l[i].v;
      while (count <= l[i].c && back_track >= 0) {
        if(solves[i - 1][back_track] != -1) {
          if(solves[i][j] != -1) {
            solves[i][j] = std::min(solves[i][j], solves[i - 1][back_track] + count);
          } else {
            solves[i][j] = solves[i - 1][back_track] + count;
          }
        }
        count++;
        back_track -= l[i].v;
      }
    }
  }
  std::cout<<solves[l.size() - 1][k]<<"\n";
  //print_mat(solves);

  vec<int> counts; // needs to be printed backwards
  int ban = l.size() - 1;
  int res = k;
  while(res > 0 || ban >= 1) {
    int count = 0;

    while((solves[ban - 1][res] > solves[ban][res] || solves[ban - 1][res] == -1) && count < l[ban].c) {
      res -= l[ban].v;
      count++;
      if(res == 0) {
        break;
      }
    }
    counts.push_back(count);
    ban--;
  }
  for (int i = counts.size() - 1; i >= 0; i--) {
    std::cout<<counts[i]<<" ";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n;
  std::cin>>n;

  l.push_back({-1, -1});
  for (int i = 0; i < n; i++) {
    int t_b;
    std::cin>>t_b;
    l.push_back({t_b, 0});
  }

  for (int i = 1; i <= n; i++) {
    int t_c;
    std::cin>>t_c;
    l[i].c = t_c;
  }

  //std::sort(l.begin(), l.end(), [](auto& r, auto& l) { return r.v < l.v; });
  int k;
  std::cin>>k;  
  solve(k); 
  
  std::cout.flush();
}
