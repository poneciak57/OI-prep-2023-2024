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

  ll n, q, m, tmp;
  std::cin>>n;

  vec<vec<int>> main(1000000);

  for(int i = 0; i < n; i++) {
    std::cin>>tmp;
    main[tmp].push_back(i);
  }

  std::cin>>q;

  while(q--) {
    std::cin>>m;

    int main_i = 0;
    bool found = true;
    for(int i = 0; i < m; i++) {
      std::cin>>tmp;
      if(found) {
        auto lb = std::lower_bound(main[tmp].begin(), main[tmp].end(), main_i);
        if(lb == main[tmp].end()) {
          found = false;
        } else {
          main_i = *lb + 1;
          // std::cout<<"LB of tmp: "<<tmp<<" main_i: "<<main_i<<" is: "<<*lb<<"\n";
        }
      }
    }
    if(found) {
      std::cout<<"TAK\n";
    } else {
      std::cout<<"NIE\n";
    }
  }

  std::cout.flush();
}
