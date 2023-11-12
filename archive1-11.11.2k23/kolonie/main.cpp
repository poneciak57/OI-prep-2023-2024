#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

struct K {
  short iq_max;
  short iq_min;
  ll weight;
  int main;
};
vec<K> kolonie;

int mFind(int i) {
  while(kolonie[i].main != i) {
    i = kolonie[i].main;
  }
  return i;
}

void mUnion(int a, int b) {
  int a_main = mFind(a);
  int b_main = mFind(b);
  if (a_main == b_main) {
    return;
  }
  kolonie[a_main].main = b_main;
  kolonie[b_main].iq_max = std::max(kolonie[b_main].iq_max, kolonie[a_main].iq_max);
  kolonie[b_main].iq_min = std::min(kolonie[b_main].iq_min, kolonie[a_main].iq_min);
  kolonie[b_main].weight = kolonie[a_main].weight + kolonie[b_main].weight;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  ll n;
  std::cin>>n;
  int i = 1;
  kolonie.push_back({0, 0, 0, 0});
  while (n--) {
    short iq;
    ll w;
    std::cin>>w>>iq;
    kolonie.push_back({iq, iq, w, i});
    i++;
  }
  str command;
  int a, b;
  while (std::cin>>command) {
    if (command == "JOIN") {
      std::cin>>a>>b;
      mUnion(a, b);
    } else if (command == "IQ_MIN") {
      std::cin>>a;
      std::cout<<kolonie[mFind(a)].iq_min<<"\n";
    } else if (command == "IQ_MAX") {
      std::cin>>a;
      std::cout<<kolonie[mFind(a)].iq_max<<"\n";
    } else if (command == "MASA") {
      std::cin>>a;
      std::cout<<kolonie[mFind(a)].weight<<"\n";
    } 
  }

  std::cout.flush();
}
