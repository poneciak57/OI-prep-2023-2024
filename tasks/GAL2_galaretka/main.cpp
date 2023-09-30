#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

vec<ll> v_corridors;

ll bin_search_highest_lower(ll g) {

  ll b = -1;
  ll e = v_corridors.size();
  ll m;
  while (b + 1 < e) {
    m = (b + e)/2;
    if (v_corridors[m] >= g) {
      e = m;
    } else {
      b = m;
    }
  }
  return e;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  ll n, m;
  std::cin>>n>>m;
  std::set<ll> s_corridors;
  ll curr_min = LLONG_MAX;
  while (n--) {
    ll c;
    std::cin>>c;
    curr_min = std::min(curr_min, c);
    s_corridors.insert(curr_min);
  }
  
  v_corridors = vec<ll>(s_corridors.begin(), s_corridors.end());

  while (m--) {
    ll g;
    std::cin>>g;
    std::cout<<bin_search_highest_lower(g)<<"\n";
  }

  std::cout.flush();
}
