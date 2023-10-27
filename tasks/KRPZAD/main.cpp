#include <bits/stdc++.h>
#include <inttypes.h>
#include <limits.h>
#include <memory>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n, t;
  std::cin>>n;
  
  vec<int> tabx(n);
  vec<int> taby(n);

  for(int i = 0; i < n; i++) {
    std::cin>>t;
    tabx[i] = t;
  }

  for(int i = 0; i < n; i++) {
    std::cin>>t;
    taby[i] = t;
  }

  for(int j = 0; j < n; j++) {
    int min_x = tabx[j];
    int min_y = taby[j];
    int min_i = j;
  
    for(int i = j; i < n; i++) {
      if(min_x * taby[i] > min_y * tabx[i]) {
        min_x = tabx[i];
        min_y = taby[i];
        min_i = i;
      }  
    }
    std::swap(tabx[j], tabx[min_i]);
    std::swap(taby[j], taby[min_i]);

  }
  
  
  for(int i = 0; i < n; i++) {
    std::cout<<tabx[i]<<" "<<taby[i]<<"\n";
  }


  std::cout.flush();
}
