#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

const ll MOD = 1e9 + 7;

struct Node {
  vec<ll> from;
  //vec<ll> to;
};

vec<Node> graf;

vec<ll> sorted;
vec<bool> visited;

void dfs(ll v) {
  visited[v] = true;
  for (auto n : graf[v].from) {
    if(!visited[n]) {
      dfs(n);
    }
  }
  sorted.push_back(v);
}

void toposort() {
  for (ll i = 1; i < graf.size(); i++) {
    if(!visited[i]) {
      dfs(i);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n, m;
  std::cin>>n>>m;
  graf = vec<Node>(n + 1, {{}});
  visited = vec<bool>(n + 1, false);
  while (m--) {
    ll a, b;
    std::cin>>a>>b;
    //graf[a].to.push_back(b);
    graf[b].from.push_back(a);
  }


  toposort();

  
  vec<ll> solves(n + 1, 0);

  solves[1] = 1;
  
  for (ll i = 1; i < sorted.size(); i++) {
    for (auto n : graf[sorted[i]].from) {
      solves[sorted[i]] += solves[n];
    }
    solves[sorted[i]] %= MOD;
  }

  std::cout<<solves[n];

  std::cout.flush();
}
