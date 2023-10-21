#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const int max_i = 1048576 + 7;

int d[max_i];

void dsb(int L, int P) {
  if(L + 1 >= P) return;

  int s = (L+P)/2;
  d[s] = d[L] + d[P];
  dsb(L, s);
  dsb(s, P);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n;
  std::cin>>n;

  if(n == 0) {
    std::cout<<"0/1 1/0";
    return 0;
  }
  int max = 2 << (n - 1);
  d[max] = 1;
  dsb(0, max);
  for(int i = 0; i <= max; i++) {
    std::cout<<d[i]<<"/"<<d[max - i]<<" ";
  }
  


  std::cout.flush();
}
