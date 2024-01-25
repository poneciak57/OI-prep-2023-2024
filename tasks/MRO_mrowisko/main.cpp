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

ll n, g, k;
int t1_root, t2_root;

vec<vec<int>> tree;
vec<ll> sub; // to substract
vec<ll> gro;
vec<int> leafs;

void dfs(int v, int par, ll mult) {
  mult = min(mult, 1000'000'007LL);
  sub[v] = mult;
  mult *= tree[v].size() - 1;
  bool is_leaf = true;
  for(auto e : tree[v]) {
    if(e == par) continue;
    is_leaf = false;
    dfs(e, v, mult);
  }
  if(is_leaf) leafs.push_back(v);
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  cin>>n>>g>>k;
  tree = vec<vec<int>>(n + 1);
  gro = vec<ll>(g);
  sub = vec<ll>(n + 1, -1);
  for(int i = 0; i < g; i++) {
    cin>>gro[i];
  }
  sort(gro.begin(), gro.end());
  cin>>t1_root>>t2_root;
  tree[t1_root].push_back(t2_root);
  tree[t2_root].push_back(t1_root);
  for(int i = 2, a, b; i < n; i++) {
    cin>>a>>b;
    tree[a].push_back(b);
    tree[b].push_back(a);
  }
  
  dfs(t1_root, t2_root, 1);
  dfs(t2_root, t1_root, 1);

  ll wyn = 0;

  for(auto l : leafs) {
    ll c = sub[l];
    ll lb = k * c;
    ll ub = k * (c + 1) - 1;
    if(c == 1) ub = lb;
    // int ile = (upper_bound(gro.begin(), gro.end(), ub) - lower_bound(gro.begin(), gro.end(), lb));
    // cout<<ile<<" \n";
    wyn += (upper_bound(gro.begin(), gro.end(), ub) - lower_bound(gro.begin(), gro.end(), lb));
  }

  cout<<wyn * k;

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