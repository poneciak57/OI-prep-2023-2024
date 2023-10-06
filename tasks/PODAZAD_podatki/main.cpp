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

  pierwsze = vec<bool>(n, true);
  pierwsze[1] = false;
  pierwsze[0] = false;

  vec<ll> to_check;
  for (ll i = 3; i < pierwsze.size(); i += 2) {
    if(pierwsze[i]) {
      ll ii = 2 * i;
      to_check.push_back(i);
      for (ll j = i + ii; j < pierwsze.size(); j+=ii) {
        pierwsze[j] = false;
      }
    }
  }
  
  ll count = 0;

  ll b = 0;
  ll e = to_check.size() - 1;

  while(b <= e) {
    long long sum = to_check[b] + to_check[e];
    if(sum >= n) {
      count += (sum == n);
      e--;
    } else {
      b++;
    }
  }

  std::cout<<count;

  

  std::cout.flush();
}
