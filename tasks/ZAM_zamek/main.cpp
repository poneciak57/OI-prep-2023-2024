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

  int n, q;
  std::cin>>n>>q;
  vec<ll> sums(n + 1);
  sums[0] = 0;
  for(int i = 1, t; i <= n; i++) {
    std::cin>>t;
    sums[i] = sums[i - 1] + t;
  }

  while(q--) {
    int x, y;
    std::cin>>x>>y;
    ll time_x = sums.back() - sums[x - 1];
    ll time_y = (sums.back() - sums[y - 1]) * 2;
    if(time_x < time_y) {
      cout<<"NIE\n";
    } else {
      cout<<"TAK\n";
    }
  }

  cout.flush();
}
