#include <algorithm>
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

  ll n;
  std::cin>>n;
  vec<ll> list(n + 1, 0);
  
  while (n--) {
    ll a, b;
    std::cin>>a>>b;
    list[a]++;
    list[b]++;
  }

  ll count = 0;
  for (auto l : list) {
    count = std::max(count, l - 1);
  }

  std::cout<<count;

  std::cout.flush();
}
