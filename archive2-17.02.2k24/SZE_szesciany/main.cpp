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

  int c = 0;
  vec<bool> v(100000, false);
  for(int i = 2; i < 100000; i++) {
    if(v[i]) continue;
    c++;
    for(int j = i+i; j < 100000; j+=i) {
      v[j] = true;
    }
  }
  cout<<c;

  cout.flush();
}
