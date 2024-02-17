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
  cin>>n;
  vec<int> tab(n);
  for(int i = 0, t; i < n; i++) {
    cin>>t;
    tab[i] = t;
  }

  sort(tab.begin(), tab.end());

  int max_c = 0;

  int b = 0, e = 0;
  while(e < tab.size()) {
    while(e - b + 1 >= 3 && tab[e] >= tab[b] + tab[b + 1]) {
      b++;
    }

    max_c = max(max_c, e - b + 1);
    e++;
  }
  cout<<max_c;
  cout.flush();
}
