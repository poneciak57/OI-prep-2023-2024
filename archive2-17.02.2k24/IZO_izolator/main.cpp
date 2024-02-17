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

  int n;
  std::cin>>n;

  int sum = 0;
  vec<int> tab(n);
  for(int i = 0; i < n; i++) {
    int tmp;
    cin>>tmp;
    sum += tmp;
    tab[i] = tmp;
  }

  sort(tab.begin(), tab.end());

  int b = 0, e = tab.size() - 1;
  while(b < e) {
    sum += tab[e] - tab[b];
    b++;
    e--;
  }
  std::cout<<sum<<"\n";

  cout.flush();
}
