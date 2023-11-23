#include <bits/stdc++.h>
#define INF 1000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;



int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n, m;
  std::cin>>n>>m;

  vec<int> mins(n + 1);

  mins[0] = INT_MAX;
  for(int i = 1; i <= n; i++) {
    int t;
    std::cin>>t;
    mins[i] = std::min(mins[i - 1], t);
  }

  int i = n + 1;
  while(m--) {
    int k;
    std::cin>>k;
    i -= 1;
    while(i > 0 && mins[i] < k) {
      i--;
    }
    
  }

  if(i < 0) {
    i = 0;
  }
  std::cout<<i;


  std::cout.flush();
}
