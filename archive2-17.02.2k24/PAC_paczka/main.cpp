#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;


void solve() {
  int n;
  cin>>n;

  int max = -1007; 
  int prev_odd = 2;
  int sum = 0;
  for(int i = 0, tmp; i < n; i++) {
    cin>>tmp;
    int oddness = std::abs(tmp) % 2;
    if(oddness == prev_odd) {
      sum = 0;
    }
    sum += tmp;
    prev_odd = oddness;

    max = std::max(max, sum);
    if(sum <= 0) {
      sum = 0;
      prev_odd = 2;
    }
  }
  cout<<max<<"\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int t;
  cin>>t;

  while(t--) {
    solve();
  }

  cout.flush();
}
