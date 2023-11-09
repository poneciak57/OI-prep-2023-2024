#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

#define INF 100000000007

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll c, n, m, w;
  std::cin>>c>>n;

  vec<ll> solves(c + 1, INF);
  solves[0] = 0;

  while(n--) {
    std::cin>>m>>w;
    for(int i = w; i <= c; i++) {
      solves[i] = std::min(solves[i], solves[i - w] + m);
    }
  }
  
  if(solves[c] == INF) {
    std::cout<<"NIEMOZLIWE";
  } else {
    std::cout<<solves[c];
  }


  std::cout.flush();
}
