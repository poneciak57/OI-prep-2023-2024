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

  ll n, m;
  std::cin>>n>>m;

  ll max = 0;
  ll cur_min = 0;
  vec<ll> przyciski(n + 1, 0);

  while(m--) {
    ll p;
    std::cin>>p;

    if(p == n+1) {
      cur_min = max;
    } else {
      przyciski[p] = std::max(cur_min, przyciski[p]) + 1;
      max = std::max(max, przyciski[p]);
    }
  }

  for (ll i = 1; i < przyciski.size(); i++)
  {
    std::cout<<std::max(cur_min, przyciski[i])<<" ";
  }
  
  std::cout.flush();
}
