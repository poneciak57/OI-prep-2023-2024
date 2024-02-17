#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

bool can_have(ll v, ll r) {
  ll c = 0;
  ll y = r;
  for(ll x = 0; x <= r; x++) {
    while((x*x + y*y) > (r*r)) {
      y--;
    };
    c += y + 1;
  }
  c -= r + 1;
  c *= 4;
  c += 1;

  return v <= c;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll v;
  std::cin>>v;

  // for(int i = 1; i < 10; i++) {
  //   can_have(-1, i);
  // }
  // return 0;

  ll b = -1, e = sqrt(v) + 7, m;
  while(b + 1 < e) {
    m = (b + e)/2;
    if(can_have(v, m)) {
      e = m;
    } else {
      b = m;
    }
  }
  std::cout<<e;

  std::cout.flush();
}
