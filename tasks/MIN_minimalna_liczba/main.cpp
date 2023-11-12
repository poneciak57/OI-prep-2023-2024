#include <bits/stdc++.h>
#define INF 1000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;



int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n, k;
  std::cin>>n>>k;

  vec<ll> tab;
  while(n--) {
    ll t;
    std::cin>>t;
    tab.push_back(t);
  }

  std::sort(tab.begin(), tab.end());


  for(ll i = k, j = 0; i < 1e18; i+=k) {
    while(tab[j] < i && (j+1) < tab.size()) {
      j++;
    }
    if(tab[j] != i) {
      std::cout<<i;
      break;
    }
  }


  std::cout.flush();
}
