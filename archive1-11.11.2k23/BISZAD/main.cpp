#include <bits/stdc++.h>
#include <string>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

str to_bin(ll n, str cur) {
  if(n == 0) {
    return cur;
  }
  cur = std::to_string(n % 2) + cur;
  return to_bin(n/2, cur);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n;
  std::cin>>n;

  std::cout<<to_bin(n, "");

  std::cout.flush();
}
