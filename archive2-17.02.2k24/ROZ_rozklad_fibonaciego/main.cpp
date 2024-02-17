#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

vec<ll> fib(86, -1);

ll gen_fib(int n) {
  if(fib[n] != -1) {
    return fib[n];
  }
  fib[n] = gen_fib(n - 1) + gen_fib(n - 2);
  return fib[n];
}

vec<bool> visited;

int fib_explode(ll num) {
  for(int i = 0; i < fib.size(); i++) {
    if(num == fib[i]) return 1;
    else if(num < fib[i]) {
      ll left = fib[i] - num;
      ll right = num - fib[i - 1];
      if(left < right) {
        return 1 + fib_explode(left);
      } else {
        return 1 + fib_explode(right);
      }
      // return 1 + std::min(fib_explode(left), fib_explode(right));
    }
  }
}


int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  fib[0] = 1;
  fib[1] = 1;

  gen_fib(85);
  // cout<<fib[85]<<"\n";

  int q;
  cin>>q;

  while(q--) {
    ll num;
    cin>>num;
    cout<<fib_explode(num)<<"\n";
  }

  cout.flush();
}
