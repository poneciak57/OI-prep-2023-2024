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

  ll n, q;

  std::cin>>n;

  vec<int> psums;
  psums.push_back(0);

  while(n--) {
    int t;
    std::cin>>t;
    psums.push_back(psums.back() + t);
  }



  std::cin>>q;
  while(q--) {
    int from, to;
    std::cin>>from>>to;
    std::cout<<psums[to] - psums[from - 1]<<"\n";
  }


  std::cout.flush();
}
