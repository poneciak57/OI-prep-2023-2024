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

  int n, m, c = 0, kap = 0, min_c = INT_MAX;
  cin>>n>>m;
  vec<int> kapustki(n);
  int b = 0;
  for(int i = 0, t; i < n; i++) {
    cin>>t;
    kapustki[i] = t;
    kap += (t == 0);
    c += (t == 1);
    // cout<<"i: "<<i<<"  c: "<<c<<"  kap: "<<kap<<"\n";
    while(c >= m) {
      c -= (kapustki[b] == 1);
      kap -= (kapustki[b] == 0);
      b++;
      min_c = min(min_c, kap);
    }
  }

  if(min_c == INT_MAX) cout<<"NIE";
  else cout<<min_c;

  cout.flush();
}
