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

  ll n, k, x, y, c = 0;
  std::cin>>n>>k>>x>>y;

  ll k_sq = k * k;
  while (n--)
  {
    ll tx, ty;
    std::cin>>tx>>ty;

    ll dist_sq = (tx - x)*(tx - x) + (ty - y)*(ty - y);
    c += dist_sq > k_sq;

  }
  
  std::cout<<c;


  std::cout.flush();
}
