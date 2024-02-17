#include <bits/stdc++.h>
#define LL_INF 10000000000000007

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

  int limit, n;
  std::cin>>limit>>n;

  vec<int> tab(n);
  for(int i = 0; i < n; i++) {
    int tmp;
    cin>>tmp;
    tab[i] = tmp;
  }

  sort(tab.begin(), tab.end());

  int b = 0, e = tab.size() - 1;
  int c = 0;
  while(b < e) {
    if((tab[b] + tab[e]) <= limit) {
      b++;
    }
    e--;
    c++;
  }
  c += b==e;
  std::cout<<c<<"\n";

  cout.flush();
}
