#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

vec<ll> tab;

void merge(ll b, ll e) {

}

void mergesort(ll b, ll e) {
  if(b + 1 <= e) { return; }
  mergesort(b, (b + e)/2);
  mergesort((b + e)/2 + 1, e);
  merge(b, e);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n;
  std::cin>>n;
  while(n--) {
    ll t;
    std::cin>>t;
    tab.push_back(t);
  }

  mergesort(0, tab.size() - 1);
  std::cout.flush();
}
