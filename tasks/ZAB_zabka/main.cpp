#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

ll n, k, m;
vec<ll> p;
vec<int> f;

/**
 * Rozwiazanie jeden dziala w czasie O(n * log_m) i korzysta z binary liftingu
 * Jest to implementacja pojedynczego binary liftingu ktora ma zlozonosc pamieciowa rzedu O(n)
*/
void solve1();

void solve2();

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>k>>m;

  f = vec<int>(n + 1);
  p = vec<ll>(n + 1);

  for(int i = 1; i <= n; i++) {
    cin>>p[i];
  }

  ll a = 1;
  f[1] = k + 1;
  for(int i = 2; i <= n; i++) {
    while(a + k + 1 <= n && p[a + k + 1] - p[i] < p[i] - p[a]) {
      a++;
    }
    if(p[i] - p[a] >= p[a + k] - p[i]) f[i] = a;
    else f[i] = a + k;
  }

  solve2();

  cout.flush();
}

vec<int> ans;
vec<vec<int>> cycles;
vec<int> state; // 0 - unvisited, 1 - in current chain, 2 - visited

struct QEntry {
  int v;
  int cycle_id;
  int cycle_pos;
};
queue<QEntry> q;

vec<vec<int>> graph;

int find_cycle(int v) {
  if(state[v] == 2) return -1;
  if(state[v] == 1) return v;

  state[v] = 1;
  int ret = find_cycle(f[v]);
  state[v] = 2;
  return ret;
}

int cycle_pos;
int cycle_id;

int getNth(int n) {
  return cycles[cycle_id][(cycle_pos + n) % cycles[cycle_id].size()];
}

vec<int> t;
void dfs(int v) {
  if(t.size() < m) ans[v] = getNth(m - t.size());
  else ans[v] = t[t.size() - m];

  t.push_back(v);
  for(auto e : graph[v]) {
    dfs(e);
  }
  t.pop_back();
}

void solve2() {
  // szukamy wszystkich cykli
  // zapisujemy te cykle w tablicy dwuwymiarowej
  state = vec<int>(n + 1, 0);

  for(int i = 1; i <= n; i++) {
    int v = find_cycle(i);
    if(v == -1) continue;

    // znajdujemy wszystkie wierzcholki danego cyklu
    vec<int> cycle;
    while(f[v] != -1) {
      int w = f[v];
      f[v] = -1;
      q.push({v, (int)cycles.size(), (int)cycle.size()});
      cycle.push_back(v);
      v = w;
    }
    cycles.push_back(cycle);
  }

  // odwracamy graf
  graph = vec<vec<int>>(n + 1);
  for(int i = 1; i <= n; i++) {
    if(f[i] == -1) continue;
    graph[f[i]].push_back(i);
  }

  ans = vec<int>(n + 1);
  while(!q.empty()) {
    auto [v, cid, cp] = q.front();
    cycle_id = cid;
    cycle_pos = cp;
    dfs(v);
    q.pop();
  }
  for(int i = 1; i <= n; i++) {
    cout<<ans[i]<<" ";
  }
}

void solve1() {
  // we apply h on g
  auto zlozenie = [&](vec<int> &g, vec<int> &h) {
    vec<int> w(n + 1);
    for(int i = 1; i <= n; i++) {
      w[i] = g[h[i]];
    }
    return w;
  };
  
  vec<int> g = f;
  vec<int> r(n + 1);
  for(int i = 1; i <= n; i++) r[i] = i;

  // traktujemy odleglosc jako liczbe binarna i uzywamy binary lifting w postaci szybkiego potegowania
  while(m > 0) {
    if(m % 2 == 1) {
      r = zlozenie(r, g);
    }
    m /= 2;
    g = zlozenie(g, g);
  }
  for(int i = 1; i <= n; i++) {
    cout<<r[i]<<" ";
  }
}