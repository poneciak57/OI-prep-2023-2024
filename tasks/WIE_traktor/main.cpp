#include <bits/stdc++.h>
#include <set>

typedef long long ll;
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

vec<Node> graph;

vec<ll> dijkstra(ll from, ll to) {
  vec<ll> d(graph.size(), LLONG_MAX);
  d[from] = 0;
  vec<ll> p(graph.size(), -1);

  std::priority_queue<llPair, vec<llPair>, std::greater<llPair>> pq;
  pq.push({0, from});
  std::set<ll> set;
  while (!pq.empty()) {
    llPair top = pq.top();
    pq.pop();

    ll cur_weight = top.first;
    ll cur_node = top.second;

    if(cur_weight > d[cur_node]) {
      continue;
    }

    for (Rel r : graph[cur_node].rels) {
      ll new_weight = cur_weight + r.weight;
      if(new_weight <= d[r.dest]) {
        p[r.dest] = cur_node;
        d[r.dest] = new_weight;
        pq.push({new_weight, r.dest});
        if (r.dest == to) {
          ll c = to;
          while (c != from) {
            set.insert(c);
            c = p[c];
          }
          set.insert(from);        
        }
      }
    }
  }

  return vec<ll>(set.begin(), set.end());
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n, m;
  std::cin>>n>>m;
  
  graph = vec<Node>(n + 1);
  
  while (m--) {
    ll a, b, c;
    std::cin>>a>>b>>c;
    graph[a].rels.push_back({c, b});
    graph[b].rels.push_back({c, a});
  }

  vec<ll> list = dijkstra(1, n);
  //std::sort(list.begin(), list.end());
  
  for (ll l : list) {
    std::cout<<l<<"\n";
  }

  std::cout.flush();
}
