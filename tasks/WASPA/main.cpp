#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

void print_mat(vec<vec<bool>> &mat) {
  for(auto row : mat) {
    for(auto v : row) {
      std::cout<<v<<" ";
    }
    std::cout<<"\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int p, t;
  ll sum = 0;
  std::cin>>p;

  vec<int> comps(p + 1);

  for(int i = 1; i <= p; i++) {
    std::cin>>t;
    sum += t;
    comps[i] = t;
  }
  std::sort(comps.begin(), comps.end(), [](const int &c1, const int &c2) { return c1 < c2; });

  ll half_of_sum = sum/2;
  vec<vec<bool>> solves(p + 1, vec<bool>(half_of_sum + 1, false));

  for(int i = 0; i <= p; i++) {
    solves[i][0] = true;
  }

  ll cur_sum = 0;
  for(int i = 1; i <= p; i++) {
    cur_sum += comps[i];
    for(int j = comps[i]; j <= std::min(half_of_sum, cur_sum); j++) {
      solves[i][j] = solves[i - 1][j] || solves[i - 1][j - comps[i]];
    }
  }

  //print_mat(solves);

  ll s = half_of_sum;
  while(!solves[p][s]) {
    s--;
  }

  std::cout<<sum - s<<" "<<s;

  std::cout.flush();
}
