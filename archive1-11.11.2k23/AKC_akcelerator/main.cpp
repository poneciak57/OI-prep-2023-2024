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

  ll n, q, w;
  std::cin>>n;
  while(n--) {
    std::cin>>w;
    tab.push_back(w);
  }

  std::sort(tab.begin(), tab.end(), [](const int &v1, const int &v2){ return v1 < v2; });

  std::cin>>q;
  while(q--) {
    ll k;
    std::cin>>k;

    int b = -1, e = tab.size(), m;
    while(b + 1 < e) {
      m = (b + e)/2;
      if(tab[m] > k) {
        e = m;
      } else {
        b = m;
      }
    }
    // std::cout<<"b1: "<<b<<", e1: "<<e<<"\n";
    if(tab[b] == k) {
      int end = b;
      b = -1; 
      e = tab.size();
      while(b + 1 < e) {
        m = (b + e)/2;
        if(tab[m] >= k) {
          e = m;
        } else {
          b = m;
        }
      }
      std::cout<<end - b<<"\n";
      // std::cout<<"b2: "<<b<<", e2: "<<e<<"\n";
    } else {
      std::cout<<"0\n";
    }
  }

  std::cout.flush();
}
