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

const int LOG = 20;
int n;

vec<int> depth;
vec<vec<int>> tree;
// [log][v]
vec<vec<int>> lca;

void dfs(int v, int par, int d) {
  depth[v] = d;
  lca[0][v] = par;
  for(int i = 1; i < LOG; i++) lca[i][v] = lca[i - 1][lca[i - 1][v]];
  for(auto e : tree[v]) {
    if(e == par) continue;
    dfs(e, v, d + 1);
  }
}

int get_dist(int a, int b) {
  if(depth[a] < depth[b]) swap(a, b);
  int k = depth[a] - depth[b];
  for(int i = LOG - 1; i >= 0; i--) {
    if(k & (1 << i)) a = lca[i][a];
  }

  if(a == b) return k;

  for(int i = LOG - 1; i >= 0; i--) {
    if(lca[i][a] != lca[i][b]) {
      a = lca[i][a];
      b = lca[i][b];
      k += (1 << i) * 2;
    }
  }
  return k + 2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n;
  tree = vec<vec<int>>(n + 1);
  depth = vec<int>(n + 1);
  lca = vec<vec<int>>(LOG, vec<int>(n + 1));

  for(int i = 1, a, b; i < n; i++) {
    cin>>a>>b;
    tree[a].push_back(b);
    tree[b].push_back(a);
  }

  dfs(1, 1, 0);

  int m, prev, curr;
  cin>>m;
  ll c = 0;
  cin>>prev;
  while(--m) {
    cin>>curr;
    c += get_dist(prev, curr);
    prev = curr;
  }
  cout<<c;

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