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

vec<vec<int>> graph;
// 0 - unvisited, 1 - in current chain, 2 - visited
vec<int> state;

bool has_cycle(int v) {
  if(state[v] == 1) return true;
  if(state[v] == 2) return false;
  state[v] = 1;
  bool ret = false;
  for(auto w : graph[v]) {
    ret = ret || has_cycle(w);
  } 
  state[v] = 2;
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  int p, s;
  cin>>p>>s;

  graph = vec<vec<int>>(p + 1);
  state = vec<int>(p + 1, 0);

  while(s--) {
    int a, b;
    cin>>a>>b;
    graph[a].push_back(b);
    // graph[b].push_back(a);
  }

  bool found = false;
  for(int i = 1; i <= p; i++) {
    found = found || has_cycle(i);
  }
  if(found) {
    cout<<"TAK";
  } else {
    cout<<"NIE";
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