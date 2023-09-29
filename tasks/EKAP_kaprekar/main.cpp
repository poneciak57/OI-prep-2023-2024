#include <bits/stdc++.h>
#include <cmath>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

ll num_sum(ll num) {
  ll sum = 0;
  while(num > 0) {
    sum += num % 10;
    num /= 10;
  }
  return sum;
}

ll how_much_go_back(ll num) {
  return ((ll)log10(num) + 1) * 9;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll k, n;
  std::cin>>k;

  while (k--) {
    std::cin>>n;
    ll end = n - how_much_go_back(n);
    bool has_result = false;
    for (ll i = end; i <= n - 1; i++) {
      if(i + num_sum(i) == n) {
        has_result = true;
        std::cout<<i<<" ";
      }
    }
    if(!has_result) {
      std::cout<<"NIE";
    }
    std::cout<<"\n";
  }
  

  std::cout.flush();
}
