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

vec<vec<int>> tree;
vec<int> val;

vec<int> dp;
vec<int> mwsr; // max_when_self_rooted

int root(int v, int par) {
  dp[v] = val[v];
  for(auto e : tree[v]) {
    if(e == par) continue;
    int r = root(e, v);
    if(r > 0) dp[v] += r;
  }
  return dp[v];
}

void do_rerooting(int v, int par) {
  // rerooting
  int par_mwsr_detached = mwsr[par];
  if(dp[v] > 0) par_mwsr_detached -= dp[v];
  if(par_mwsr_detached > 0) mwsr[v] = par_mwsr_detached + dp[v];
  else mwsr[v] = dp[v];

  // recursive call
  for(auto e : tree[v]) {
    if(e == par) continue;
    do_rerooting(e, v);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n;
  cin>>n;
  tree = vec<vec<int>>(n + 1);
  val = vec<int>(n + 1);
  dp = vec<int>(n + 1);
  mwsr = vec<int>(n + 1);
  for(int i = 1, tmp; i <= n; i++) {
    cin>>tmp;
    if(tmp == 1) val[i] = 1;
    else val[i] = -1;
  }

  for(int i = 1, a, b; i < n; i++) {
    cin>>a>>b;
    tree[a].push_back(b);
    tree[b].push_back(a);
  }

  root(1, 1);
  do_rerooting(1, 1);

  for(int i = 1; i <= n; i++) {
    cout<<mwsr[i]<<" ";
  }

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