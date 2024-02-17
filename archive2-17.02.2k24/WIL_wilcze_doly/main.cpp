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

ll n, p, d;
vec<ll> pref_sums;
// wartosc deski polozonej od itego dolu
vec<ll> plank_value;

struct MQueue {
  deque<pair<ll, int>> dq;

  ll max() {
    if(dq.empty()) return 0;
    return dq.front().first;
  }

  void push(ll v) {
    int c = 0;
    while(!dq.empty() && dq.back().first <= v) {
      c += dq.back().second + 1;
      dq.pop_back();
    }
    dq.push_back({v, c});
  }

  void pop() {
    if(dq.empty()) return;
    if(dq.front().second == 0) dq.pop_front();
    else dq.front().second--;
  }
};  

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  cin>>n>>p>>d;
  pref_sums = vec<ll>(n + 1, 0);
  plank_value = vec<ll>(n + 1, 0);

  for(int i = 1, tmp; i <= n; i++) {
    cin>>tmp;
    pref_sums[i] = pref_sums[i - 1] + tmp;
  }
  for(int i = 1; i <= n; i++) plank_value[i] = pref_sums[min(i + d, n)] - pref_sums[i - 1];

  MQueue mq;
  int wynik = d;
  int j = d;
  for(int i = 1; i <= n - d + 1; i++) {
    if(mq.dq.empty()) {
      mq.push(plank_value[i]);
      mq.push(plank_value[i + 1]);
    }
    j = max(j, (int)(i + d - 1));
    while(j + 1 <= n && (pref_sums[j + 1] - pref_sums[i - 1] - mq.max()) <= p) {
      j++;
      mq.push(plank_value[j - d + 1]);
    }
    wynik = max(wynik, j - i + 1);
    mq.pop();
  }

  cout<<wynik;
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