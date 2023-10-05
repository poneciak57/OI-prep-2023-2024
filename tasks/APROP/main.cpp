#include <bits/stdc++.h>
#include <iostream>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

vec<ll> results(91, -1);

ll prof(ll n) {
  if(results[n] == -1) {
    results[n] = prof(n - 1) + prof(n - 2);
    return results[n];
  }
  return results[n];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n;
  std::cin>>n;
  results[0] = 1;
  results[1] = 1;
  std::cout<<prof(n);


  std::cout.flush();
}
