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

  ll n, m, z;
  ll p, k, l;
  bool can = true;

  std::cin>>n>>m>>z;
  vec<ll> pociag(n + 1, m);


  while(z--) {
    can = true;
    std::cin>>p>>k>>l;
    for (ll i = p; i < k; i++) {
      if(pociag[i] < l) {
        can = false;
        std::cout<<"N\n";
        break;
      }
    }

    if(can) {
      std::cout<<"T\n";
      for (ll i = p; i < k; i++) {
        pociag[i] -= l;
      }
    }
    
  }

  std::cout.flush();
}
