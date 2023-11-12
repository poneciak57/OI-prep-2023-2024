#include <bits/stdc++.h>
#define INF 1000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;



int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  vec<int> costs;
  vec<int> commute_costs;
  ll minv = 10e9+ 7;
  ll n;
  std::cin>>n;

  for(ll i = 0, c; i < n; i++) {
    std::cin>>c;
    costs.push_back(c);
    minv = std::min(minv, c);
  }


  commute_costs.push_back(0);
  for(int i = 1, c; i < n; i++) {
    std::cin>>c;
    commute_costs.push_back(commute_costs.back() + c);
  }

  ll maxv = 0;
  int b = 0, e = 1;

  // sprzedajemy w b od lewej
  while((b+1) < costs.size()) {
    ll commute_cost_b_e = commute_costs[e] - commute_costs[b];
    ll max_value = costs[b] - commute_cost_b_e - minv;
    if(max_value <= maxv) {
      b++;
      e = b+1;
      continue;
    }

    ll curr_value = costs[b] - commute_cost_b_e - costs[e];
    maxv = std::max(maxv, curr_value);
    e++;
    if(e >= costs.size()) {
      b++;
      e = b+1;
    }
  }

  b = costs.size() - 1; 
  e = b-1;
  while((b-1) >= 0) {
    ll commute_cost_b_e = commute_costs[b] - commute_costs[e];
    ll max_value = costs[b] - commute_cost_b_e - minv;
    if(max_value <= maxv) {
      b--;
      e = b-1;
      continue;
    }

    ll curr_value = costs[b] - commute_cost_b_e - costs[e];
    maxv = std::max(maxv, curr_value);
    e--;
    if(e < 0) {
      b--;
      e = b-1;
    }
  }

  std::cout<<maxv;

  std::cout.flush();
}
