#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const int MAX_S = 5 * 1e5 + 7;
vec<int> tab(MAX_S, 0);

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n;
  cin>>n;
  for(int i = 0, tmp; i < n; i++) {
    cin>>tmp;
    tab[tmp]++;
  }
  sort(tab.begin(), tab.end(), [](int i1, int i2) { return i1 > i2; });

  int c = 0;
  int b = 0, e = MAX_S - 1;
  while(tab[e] == 0) e--;
  while(b <= e) {
    int v = tab[b] - 1;
    c++;

    while(v > 0) {
      int v_snap = v;
      v -= tab[e];
      tab[e] -= v_snap;
      if(tab[e] <= 0) e--;
    }
    b++;
  }
  cout<<c;

  cout.flush();
}