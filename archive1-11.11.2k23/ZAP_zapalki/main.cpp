#include <algorithm>
#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n;
  std::cin>>n;

  ll zeros = 0;
  ll ones = 0;
  // {0, 1}
  vec<llPair> to_check;

  ll prev;
  std::cin>>prev;
  ones+=prev;
  zeros+=(prev==0);
  while (--n) {
    ll cur;
    std::cin>>cur;
    if(cur == 0 && prev == 1) {
      to_check.push_back({zeros, ones});
    }

    ones += cur;
    zeros += (cur==0);

    prev = cur;
  }

  ll min = std::min(zeros, ones);

  for (auto pair : to_check) {
    ll left_zeros = pair.first;
    ll left_ones = pair.second;
    ll right_zeros = zeros - left_zeros;
    ll right_ones = ones - left_ones;

    min = std::min(min, right_ones + left_zeros);
  }

  std::cout<<min;
  std::cout.flush();
}
