#include <bits/stdc++.h>
#include <type_traits>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  int n;
  std::cin>>n;

  vec<int> tab;
  tab.push_back(-1);

  while(n--) {
    int t;
    std::cin>>t;
    tab.push_back(t);
  }

  ll count = 0;

  for(int j = 1; j < tab.size(); j++) {
    int i = j;
    while(i >= 1) {
      count+= tab[j] < tab[i];
      i--;
    }
  }

  std::cout<<count;


  std::cout.flush();
}
