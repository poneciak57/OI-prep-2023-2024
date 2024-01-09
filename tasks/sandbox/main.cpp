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

  double sum = 0;
  int n, m;
  cin>>n>>m;

  vec<double> kwoty(n + 1, 0);

  while(m--) {
    char c;
    int a;
    cin>>c>>a;
    if(c == 'W') {
      kwoty[a] = sum / n;
      n--;
      sum -= kwoty[a];
    } else {
      sum += a;
    }
  }

  for(int i = 1; i < kwoty.size(); i++) {
    cout<<fixed<<setprecision(4)<<kwoty[i]<<" ";
  }




  cout.flush();
}
