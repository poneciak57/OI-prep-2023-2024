#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int d, n, price;
  std::cin>>d>>n;
  vec<int> solves(d + 1, 0);

  for(int i = 1; i <= n; i++) {
    std::cin>>price;
    for(int j = i; j <= d; j++) {
      solves[j] = std::max(solves[j], solves[j - i] + price);
    }
  }


  std::cout<<solves[d];

  std::cout.flush();
}
