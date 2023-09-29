#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

bool is_divisible(ll num) {
  ll num_snap = num;
  while(num_snap > 0) {
    ll cur_num = num_snap % 10;

    if(cur_num == 0 || num % cur_num != 0) {
      return false;
    }

    num_snap /= 10;
  }
  return true;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  ll n;
  std::cin>>n;
  n += 1;
  while(!is_divisible(n)) {
    n++;
  }
  std::cout<<n;

  std::cout.flush();
}
