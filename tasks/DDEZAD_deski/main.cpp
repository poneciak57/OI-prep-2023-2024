#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

vec<int> tab;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n, s;
  std::cin>>n>>s;

  while(n--) {
    int l;
    std::cin>>l;
    if(l < s) {
      tab.push_back(l);
    }
  }
  std::sort(tab.begin(), tab.end(), [](const int &v1, const int &v2){ return v1 < v2; });

  for(int i = 0; i < tab.size(); i++) {
    int v = s - tab[i];
    int b = i, e = tab.size(), m;

    while(b + 1 < e) {
      m = (b + e)/2;
      if(tab[m] <= v) {
        b = m;
      } else {
        e = m;
      }
    }

    if(tab[b] == v) {
      std::cout<<tab[i]<<" "<<tab[b];
      break;
    }
  }

  std::cout.flush();
}
