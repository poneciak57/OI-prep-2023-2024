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
int max_v = 0;
vec<vec<int>> tree;

// pion biorac pod uwage mozliwosc pojedynczego wierzcholka
vec<int> pion;
vec<int> fakt_pion;
vec<int> wyn;

void dp(int v, int par) {
  int d = tree[v].size();
  pion[v] = d;
  int max_pion1 = 0;
  int max_pion2 = 0;
  for(auto w : tree[v]) {
    if(w == par) continue;
    dp(w, v);
    pion[v] = max(pion[v], pion[w] - 1 + d - 1);
    fakt_pion[v] = max(fakt_pion[v], pion[w] - 1 + d - 1);
    if(pion[w] >= max_pion1) {
      max_pion2 = max_pion1;
      max_pion1 = pion[w];
    } else if(pion[w] > max_pion2) {
      max_pion2 = pion[w];
    }
  }
  max_v = max({max_v, fakt_pion[v], max_pion1 + max_pion2 - 2 + d - 2});
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  cin>>n;
  tree = vec<vec<int>>(n + 1); 
  pion = vec<int>(n + 1);
  fakt_pion = vec<int>(n + 1);
  wyn = vec<int>(n + 1);
  for(int i = 1, a, b; i < n; i++) {
    cin>>a>>b;
    tree[a].push_back(b);
    tree[b].push_back(a);
  }

  dp(1, -1);
  cout<<max_v;

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