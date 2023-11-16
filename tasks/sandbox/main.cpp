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

  std::stack<ll> heights;
  heights.push(0);
  ll count = 0;
  while(n--) {
    ll len, height;
    std::cin>>len>>height;

    while(heights.top() > height) {
      heights.pop();
    }

    if(heights.top() != height) {
      count++;
    }
    heights.push(height);
  }

  std::cout<<count;


  std::cout.flush();
}
