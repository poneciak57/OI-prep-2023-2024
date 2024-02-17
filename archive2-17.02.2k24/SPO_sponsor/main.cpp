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

int n;
int solve(vec<int> &wyn) {
  vec<int> p(n, 0);
  int len = 0;
  for(auto w : wyn) {
    int b = -1, e = n, m;
    while(b + 1 < e) {
      m = (b + e) / 2;
      if(p[m] > w) {
        b = m;
      } else {
        e = m;
      }
    }
    if(e == len) {
      len++;
    }
    p[e] = w;
  }
  return len;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  cin>>n;

  vec<int> wyn(n);
  double inp;
  for(int i = 0; i < n; i++) {
    cin>>inp;
    wyn[i] = inp * 10000;
  }

  cout<<(ll)solve(wyn) * 100;

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