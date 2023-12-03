#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;


int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n;
  std::cin>>n;

  vec<int> tab(n);
  for(int i = 0; i < n; i++) {
    std::cin>>tab[i];
  }
  sort(tab.begin(), tab.end());

  if(n == 1) {
    cout<<tab[0];
  } else {
    int sum = tab[1];
    int small1 = tab[0];
    int small2 = tab[1];
    int e = tab.size() - 1;
    while (e >= 2)
    {
      if(e == 2) {
        sum += small1 + tab[e];
        e--;
      } else {
        int one_by_one = small1 * 2 + tab[e] + tab[e - 1];
        int together = small1 + tab[e] + small2*2;
        if(one_by_one <= together) {
          sum += small1 + tab[e];
          e--;
        } else {
          sum += together;
          e-=2;
        }
      }
    }
    
    
    cout<<sum;
  }

  cout.flush();
}
