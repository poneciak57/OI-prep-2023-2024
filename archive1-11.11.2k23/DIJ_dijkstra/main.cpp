#include <bits/stdc++.h>

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

ll n, m;
vec<Node> graf;

ll dijkstra(ll src, ll dest) {
  // holds distance from src to given node, initialized with infiniti
  vec<ll> d(n + 1, LLONG_MAX);

  d[src] = 0; // set the distance from src to src to 0
    
  // holds previous node for given node
  vec<ll> p(n + 1, -1);

  // priority queue for holding pairs of {current weight, current node} in asceding order by weight 
  // so we are always prioritizing those with lower distance from source so the first time we get to dest we know its the 
  // shortest path
  std::priority_queue<llPair, vec<llPair>, std::greater<llPair>> pq;
  pq.push({0, src});  // Push the starting node into the priority queue with weight 0

  while (!pq.empty()) {
    llPair top = pq.top();
    pq.pop();
    ll cur_weight = top.first;
    ll cur_node = top.second;

    // if the current weight is higher than weight of current node
    if (cur_weight > d[cur_node]) {
      continue;  // Skip outdated nodes
    }

    // if we find the dest node we return the distance to the node we know its the lowest cause of prior queue
    if(cur_node == dest) {
      return d[dest];
    }

    // we iterate over relations of node and for each relation we check if distance from current node 
    // to the node from relation is lower than existing one
    // if so we push the node to the queue and set his new distance
    for (Rel r : graf[cur_node].rels) {
      ll new_dist = d[cur_node] + r.weight;
      if (new_dist < d[r.dest]) {
        d[r.dest] = new_dist;
        p[r.dest] = cur_node;
        pq.push({new_dist, r.dest});
      }
    }
  }

  // return -1 if we cannot reach the dest from the source
  return -1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>n>>m;

  graf = vec<Node>(n + 1);

  for (ll i = 0, a, b, c; i < m; i++) {
    std::cin>>a>>b>>c;
    graf[a].rels.push_back({c, b});
    graf[b].rels.push_back({c, a});
  }

  std::cout<<dijkstra(1, n);

  std::cout.flush();
}

/// TO COPY ///
/*

ll dijkstra(ll src, ll dest) {
  vec<ll> d(n + 1, LLONG_MAX);
  d[src] = 0;
  vec<ll> p(n + 1, -1);
  std::priority_queue<llPair, vec<llPair>, std::greater<llPair>> pq;
  pq.push({0, src});  // Push the starting node into the priority queue with weight 0

  while (!pq.empty()) {
    llPair top = pq.top();
    pq.pop();
    ll cur_weight = top.first;
    ll cur_node = top.second;

    if (cur_weight > d[cur_node]) {
      continue;  // Skip outdated nodes
    }

    if(cur_node == dest) {
      return d[dest];
    }

    for (Rel r : graf[cur_node].rels) {
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

*/