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


  ll prev1;
  ll prev2 = 0;
  std::cin>>prev1;
  ll res;
  while (--n) {
    ll cur;
    std::cin>>cur;

    res = std::min(prev2 + cur, prev1 + cur);
    prev2 = prev1;
    prev1 = res;
  }

  std::cout<<std::min(prev2, prev1);
  std::cout.flush();
}
