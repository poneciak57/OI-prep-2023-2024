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

ll n;
vec<Node> graf;

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