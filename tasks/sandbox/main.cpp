#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

int buckets[1000001];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n;
  std::cin>>n;

  while(n--) {
    int t;
    std::cin>>t;
    buckets[t]++;
  }

  for(int i = 0; i<=1000000; i++) {
    while(buckets[i]--) {
      std::cout<<i<<" ";
    }
  }

  std::cout.flush();
}
