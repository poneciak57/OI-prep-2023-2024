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

  str s1, s2;
  cin>>s1>>s2;

  s1 = " " + s1;
  s2 = " " + s2;

  // [s1][s2]
  vec<vec<int>> dp(s1.size(), vec<int>(s2.size(), 0));

  for(int i1 = 1; i1 < s1.size(); i1++) {
    for(int i2 = 1; i2 < s2.size(); i2++) {
      dp[i1][i2] = max({dp[i1 - 1][i2], dp[i1][i2 - 1], dp[i1 - 1][i2 - 1] + (s1[i1] == s2[i2])});
    }
  }

  cout<<dp[s1.size() - 1][s2.size() - 1]<<"\n";

  int j = s2.size() - 1;
  str s = "";
  for(int i = s1.size() - 1; i > 0; i--) {
    while((j - 1) > 0 && dp[i][j] == dp[i][j-1]) j--;
    if(dp[i][j] != dp[i - 1][j]) {
      s += s1[i];
    }
  }

  reverse(s.begin(), s.end());
  cout<<s;

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