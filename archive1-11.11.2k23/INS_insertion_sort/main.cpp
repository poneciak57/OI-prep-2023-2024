#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

vec<int> tab;

void insertion_sort() {
  int n = tab.size();
  int i = 1;
  
  while(i < n) {
    int j = i - 1;
    int k = tab[i];

    while(j >= 0 && tab[j] > k) {
      tab[j + 1] = tab[j];
      j--;
    }
    tab[j + 1] = k;
    i++;
  }
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n;
  std::cin>>n;

  while(n--) {
    int t;
    std::cin>>t;
    tab.push_back(t);
  }

  insertion_sort();

  for(auto i : tab) {
    std::cout<<i<<" ";
  }

  std::cout.flush();
}
