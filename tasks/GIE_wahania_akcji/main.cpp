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

  vec<int> sums(10000, 0);

  str s;
  int max_inc = 0;
  while(getline(cin, s)) {
    istringstream line(s);
    int i = 0;
    int tmp;
    while(line>>tmp) {
      if(tmp == -99) {
        sums.erase(sums.begin() + i);
        sums.push_back(0);
        continue;
      }
      sums[i] += tmp;
      if(sums[i] < 0) sums[i] = 0;
      max_inc = max(max_inc, sums[i]);
      i++;
    }
  }
  cout<<max_inc;

  cout.flush();
}
