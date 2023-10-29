#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

vec<ll> tab;

void merge(ll b, ll e) {
  vec<ll> temp;
  std::copy(tab.begin() + b, tab.begin() + e, std::back_inserter(temp));

  ll mid = temp.size() / 2;
  ll start1 = 0, start2 = mid;
  ll i = b;

  while(start1 < mid && start2 < temp.size()) {
    if(temp[start1] < temp[start2]) {
      tab[i] = temp[start1]; 
      start1++;
    } else {
      tab[i] = temp[start2];
      start2++;
    }
    i++;
  }

  while (start1 < mid)
  {
    tab[i] = temp[start1];
    start1++;
    i++;
  }

  while (start2 < temp.size())
  {
    tab[i] = temp[start2];
    start2++;
    i++;
  }

}

void mergesort(ll b, ll e) {
  if(b + 1 >= e) { return; }
  // std::cout<<"mergesort: "<<b<<" "<<e<<"\n";
  mergesort(b, (b + e)/2);
  mergesort((b + e)/2, e);
  merge(b, e);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n;
  std::cin>>n;
  while(n--) {
    ll t;
    std::cin>>t;
    tab.push_back(t);
  }

  mergesort(0, tab.size());

  for(auto i : tab) {
    std::cout<<i<<" ";
  }
  std::cout.flush();
}
