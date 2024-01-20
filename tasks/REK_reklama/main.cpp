#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1000992299;

ll powm(ll a, ll n, ll MOD);
ll multm(ll a, ll b, ll MOD);
ll divm(ll a, ll b, ll MOD);

inline int rand_range(int from, int to) {
  return (rand() % (to - from + 1)) + from;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  int n, m, k;
  cin>>n>>m>>k;

  vec<int> screens(n + 1);
  vec<int> owners(m + 1);

  for(int i = 1; i <= n; i++) {
    cin>>screens[i];
  }

  for(int i = 1; i <= m; i++) {
    cin>>owners[i];
  }

  int b = 1, max_c = 0;
  vec<int> used_screens(m + 1, 0);
  for(int i = 1; i <= n; i++) {
    if(used_screens[screens[i]] == 0) {
      k -= owners[screens[i]];
    }
    used_screens[screens[i]]++;
    while(k < 0) {
      used_screens[screens[b]]--;
      if(used_screens[screens[b]] == 0) k += owners[screens[b]];
      b++;
    }
    max_c = max(max_c, i - b + 1);
  } 

  cout<<max_c;

  cout.flush();
}





ll powm(ll a, ll n, ll MOD) {
  ll w = 1;

  while (n > 0) {
    if (n % 2 == 1)
      w = (w * a) % MOD;
      a = (a * a) % MOD;
      n /= 2;
  }
  return w;
}

ll multm(ll a, ll b, ll MOD) {
  return (a * b) % MOD;
}

ll divm(ll a, ll b, ll MOD) {
  return multm(a, powm(b, MOD - 2, MOD), MOD);
}