#include <bits/stdc++.h>
#include <limits.h>

typedef int ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Rel {
  ll weight;
  ll dest;
};

struct Node {
  vec<Rel> rels;
};

ll dijkstra(vec<Node> g, ll from, ll to) {
  vec<ll> d(g.size(), INT_MAX);
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

    for (Rel r : g[cur_node].rels) {
      ll new_dist = d[cur_node] + r.weight;
      if (new_dist < d[r.dest]) {
        d[r.dest] = new_dist;
        p[r.dest] = cur_node;
        pq.push({new_dist, r.dest});
      }
    }
  }

  return -1;
}

ll n, m;
vec<Node> graph;

ll min = INT_MAX;

void dfs(ll weight, vec<ll> cpath, ll curr) {
  cpath.push_back(curr);
  if(curr == n) {
    vec<Node> g = graph;
    for(ll i = 0; i < (cpath.size() - 1); i++) {
      ll to_del = cpath[i+1];
      ll p = cpath[i];
      g[p].rels.erase(
        std::remove_if(
          g[p].rels.begin(), 
          g[p].rels.end(), 
          [to_del](const Rel& r) { 
            return r.dest == to_del;
        }), 
        g[p].rels.end()
      );
    }
    ll dij = dijkstra(g, 1, n);
    if(dij != -1) {
      min = std::min(min, weight + dij);
    }
  }

  for (Rel r : graph[curr].rels) {
    dfs(weight + r.weight, cpath, r.dest);
  }
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>n>>m;

  graph = vec<Node>(n + 1);

  while (m--) {
    ll a, b, c;
    std::cin>>a>>b>>c;
    graph[a].rels.push_back({c, b});
  }


  dfs(0, {}, 1);

  if(min == INT_MAX) {
    std::cout<<-1;
  } else {
    std::cout<<min;
  }


  std::cout.flush();
}
