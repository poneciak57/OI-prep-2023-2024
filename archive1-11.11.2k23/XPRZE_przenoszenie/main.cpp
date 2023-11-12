#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

ll count_moves(ll n, ll m) {
  ll bonus = 0;
  ll count = 0;
  while(n > 0 || m > 0) {
    ll nd = n % 10;
    ll md = m % 10;
    if((nd + md + bonus) >= 10) {
      bonus = 1;
      count++;
    } else {
      bonus = 0;
    }
    n /= 10;
    m /= 10;
  }
  return count;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll q;
  std::cin>>q;

  while(q--) {
    ll n, m;
    std::cin>>n>>m;
    std::cout<<count_moves(n, m)<<"\n";
  } 

  std::cout.flush();
}
