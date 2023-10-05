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

  ll b1 = 0, b2 = 0, b3 = 0;

  ll res;


  while (n--) {
    ll c;
    std::cin>>c;

    res = std::max(c + b3, std::max(c + b2, b1));
    b3 = b2;
    b2 = b1;
    b1 = res;
  }

  std::cout<<res;
  std::cout.flush();
}
