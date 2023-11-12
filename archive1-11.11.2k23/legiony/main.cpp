#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const ll MOD = 1e9 + 7;

ll fpow(ll n, ll pow) {
  if(pow == 0) {
    return 1;
  }
  if(pow % 2) {
    return (n * fpow(n, pow - 1)) % MOD;
  } else {
    ll p = fpow(n, pow/2);
    return (p * p) % MOD;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll q;
  std::cin>>q;
  while (q--) {
    ll r, k, b, m;
    std::cin>>r>>k>>b>>m;
    std::cout<<(fpow(r, k) * fpow(b, m)) % MOD<<"\n";
  }

  std::cout.flush();
}
