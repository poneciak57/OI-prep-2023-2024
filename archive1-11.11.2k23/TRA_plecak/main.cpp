#include <bits/stdc++.h>

typedef int ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n, k;
  std::cin>>n>>k;

  vec<vec<long long>> results(n + 1, vec<long long>(k + 1, 0));
  
  // { weight, point } 
  vec<llPair> items;
  items.push_back({0, 0});

  ll nn = n;
  while (nn--) {
    ll w, u;
    std::cin>>w>>u;
    items.push_back({w, u});
  }

  for (ll i = 1; i <= n; i++) {
    for (ll w = 1; w <= k; w++) {
      // if item can be fit in weight
      ll before_weight_index = ((w < items[i].first) ? 0 : (w - items[i].first));
      if((items[i].first <= w) && ((items[i].second + results[i - 1][before_weight_index]) >= results[i - 1][w])) {
        results[i][w] = items[i].second + results[i - 1][before_weight_index];
      } else {
        results[i][w] = results[i - 1][w];
      }
    }
  }

  /*
  for (auto row : results) {
    for (auto c : row) {
      std::cout<<c<<" ";
    }
    std::cout<<"\n";
  }
  */
  std::cout<<results[n][k];

  std::cout.flush();
}
