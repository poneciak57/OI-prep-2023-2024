#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Node {
  ll height;
  vec<ll> rels;
};

vec<Node> graph;


ll dijkstra(ll from, ll to) {
  vec<ll> d(graph.size(), LLONG_MAX);
  d[from] = graph[from].height;
  vec<ll> p(graph.size(), -1);
  
  std::priority_queue<llPair, vec<llPair>, std::greater<llPair>> pq;
  pq.push({graph[from].height, from});
  while (!pq.empty()) {
    llPair top = pq.top();
    pq.pop();

    ll cur_height = top.first;
    ll cur_node = top.second;

    if(cur_height > d[cur_node]) {
      continue;
    }

    for (ll r : graph[cur_node].rels) {
      ll new_height = std::max(d[cur_node], graph[r].height);
      if(new_height < d[r]) {
        d[r] = new_height;
        p[r] = cur_node;
        pq.push({new_height, r});
      }
    }
  }
 
  if(p[to] != -1) {
    return d[to];
  } else {
    return -1;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n, m;
  std::cin>>n>>m;
  
  graph = vec<Node>(n + 1);

  for (ll i = 1; i <= n; i++) {
    ll h;
    std::cin>>h;
    graph[i] = {h, {}};
  }

  while (m--) {
    ll from, to;
    std::cin>>from>>to;
    graph[from].rels.push_back(to);
    graph[to].rels.push_back(from);
  }
  
  std::cout<<dijkstra(1, n);


  std::cout.flush();
}
