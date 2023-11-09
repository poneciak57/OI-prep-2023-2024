#include <bits/stdc++.h>

template <typename T>
using vec = std::vector<T>;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int p;
  int sum = 0;
  std::cin>>p;

  vec<int> comps(p + 1);

  for(int i = 1; i <= p; i++) {
    std::cin>>comps[i];
    sum += comps[i];
  }
  std::sort(comps.begin(), comps.end(), [](const int &c1, const int &c2) { return c1 < c2; });

  int half_of_sum = sum/2;
  vec<bool> solves(half_of_sum + 1, false);

  solves[0] = true;

  int cur_sum = 0;
  for(int i = 1; i <= p; i++) {
    int cc = comps[i];
    cur_sum += cc;
    int min = std::min(half_of_sum, cur_sum);
    for(int j = min; j >= cc; j--) {
      if(solves[j - cc]) {
        solves[j] = true;
      }
    }
  }

  int s = half_of_sum;
  while(!solves[s]) {
    s--;
  }

  std::cout<<sum - s<<" "<<s;

  std::cout.flush();
}
