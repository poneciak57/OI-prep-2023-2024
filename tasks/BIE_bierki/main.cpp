#include <algorithm>
#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

vec<ll> bierki;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  ll n;
  std::cin>>n;

  while (n--) {
    ll b;
    std::cin>>b;
    bierki.push_back(b);
  }

  std::sort(bierki.begin(), bierki.end());

  ll b = 2;
  ll e = 0;
  ll max = 0;
  while (b < bierki.size()) {
    if(b - e < 2) {
      b++;
    }
    if(bierki[e] + bierki[e+1] <= bierki[b]) {
      e++;
    } else { 
      b++;
    }
    max = std::max(max, b - e);
  }

  std::cout<<max;


  std::cout.flush();
}
