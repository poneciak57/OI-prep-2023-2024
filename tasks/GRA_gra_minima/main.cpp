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

  int prev = tab[0];
  for(int i = 1; i < n; i++) {
    prev = max(prev, tab[i] - prev);
  }

  cout<<prev;


  cout.flush();
}
