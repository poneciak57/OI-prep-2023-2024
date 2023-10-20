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

  ll to_c = 0;
  ll c = 0;

  while(n--) {
    bool t;
    std::cin>>t;

    if(t) {
      c += to_c;
    } else {
      to_c++;
    }
  }

  std::cout<<c;

  std::cout.flush();
}
