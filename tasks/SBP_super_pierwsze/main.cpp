#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

vec<bool> pierwsze;


ll num_sum(ll n) {
  ll sum = 0;
  while (n > 0) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}

ll bin_num_sum(ll n) {
  ll sum = 0;
  while (n > 0) {
    sum += n % 2;
    n /= 2;
  }
  return sum;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n, m;
  std::cin>>n>>m;
  pierwsze = vec<bool>(m + 3, true);
  pierwsze[1] = false;
  pierwsze[0] = false;

  for (ll i = 2; i < pierwsze.size(); i++) {
    if(pierwsze[i]) {
      for (ll j = i + i; j < pierwsze.size(); j+=i) {
        pierwsze[j] = false;
      }
    }
  }

  ll count = 0;
  for (ll i = n; i <= m; i++) {
    //count += (pierwsze[i] && pierwsze[num_sum(i)] && pierwsze[bin_num_sum(i)]);
    if (pierwsze[i] && pierwsze[num_sum(i)] && pierwsze[bin_num_sum(i)]) {
      std::cout<<i<<"\n";
    }
  }


  std::cout<<count;


  std::cout.flush();
}
