#include <algorithm>
#include <bits/stdc++.h>
#include <limits.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

vec<ll> tunels;

ll bin_search_tunel(ll height) {
  ll b = -1;
  ll e = tunels.size();
  ll m;
  while (b + 1 < e) {
    m = (b + e) / 2;
    if(tunels[m] > height) {
      b = m;
    } else {
      e = m;
    }
  }
  return e;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  ll a, b;
  std::cin>>a>>b;

  ll cur_min = LLONG_MAX;
  while (a--) {
    ll t;
    std::cin>>t;
    cur_min = std::min(cur_min, t);
    tunels.push_back(cur_min);
  }
  
  while (b--) {
    ll h;
    std::cin>>h;
    std::cout<<bin_search_tunel(h)<<" ";
  }

  std::cout.flush();
}
