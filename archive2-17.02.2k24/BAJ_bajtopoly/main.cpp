#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const ll MOD = 1e9 + 7;

ll powm(ll a, ll n) {
  ll w = 1;

  while (n > 0) {
    if (n % 2 == 1)
      w = (w * a) % MOD;
      a = (a * a) % MOD;
      n /= 2;
  }
  return w;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  ll k, n;
  cin>>k>>n;
  ll wyn = 1;
  ll prev = 4;
  for(int i = 1; i < k; i++) {
    prev = prev * prev % MOD;
    wyn = wyn * prev % MOD;
  }
  cout<<(6 * wyn) % MOD;

  cout.flush();
}
