#include <bits/stdc++.h>
#include <limits.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

ll n, m;

ll dijkstra(vec<vec<ll>> g, ll from, ll to) {
  vec<ll> d(g.size(), LLONG_MAX);
  d[from] = 0;
  vec<ll> p(g.size(), -1);
  std::priority_queue<llPair, vec<llPair>, std::greater<llPair>> pq;
  pq.push({0, from});

  while (!pq.empty()) {
    llPair top = pq.top();
    pq.pop();
    ll cur_weight = top.first;
    ll cur_node = top.second;

    if (cur_weight > d[cur_node]) {
      continue;
    }

    if(cur_node == to) {
      return d[to];
    }

    for(ll i = 1; i < (n + 1); i++) {
      if(g[cur_node][i] > 0) {
        ll new_dist = d[cur_node] + g[cur_node][i];
        if(new_dist < d[i]) {
          d[i] = new_dist;
          p[i] = cur_node;
          pq.push({new_dist, i});
        }
      }
    } 
  }

  return -1;
}

vec<vec<ll>> graph;

ll min = LLONG_MAX;

vec<ll> cpath;

void dfs(ll weight, ll curr) {
  cpath.push_back(curr);
  if(curr == n) {
    vec<vec<ll>> g = graph;
    for(ll i = 0; i < (cpath.size() - 1); i++) {
      ll to_del = cpath[i+1];
      ll p = cpath[i];
      g[p][to_del] = 0;
    }
    ll dij = dijkstra(g, 1, n);
    if(dij != -1) {
      min = std::min(min, weight + dij);
    }
  }

  for(ll i = 1; i < (n + 1); i++) {
    if(graph[curr][i] > 0) {
      dfs(weight + graph[curr][i], i);
    }
  }
  cpath.pop_back();
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>n>>m;

  graph = vec<vec<ll>>(n + 1, vec<ll>(n + 1, 0));

  while (m--) {
    ll a, b, c;
    std::cin>>a>>b>>c;
    graph[a][b] = c;
  }


  dfs(0, 1);

  if(min == LLONG_MAX) {
    std::cout<<-1;
  } else {
    std::cout<<min;
  }


  std::cout.flush();
}
