#include <algorithm>
#include <bits/stdc++.h>
#include <limits.h>
#include <queue>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

ll n, m;

struct QEntry {
  int from;
  int to;
  ll weight;
};

struct GreaterWeight {
  bool operator()(QEntry const& qe1, QEntry const& qe2) {
    return qe1.weight > qe2.weight;
  }
};

//graph[from][to] = weight or -1
vec<vec<int>> graph;

ll dijkstra(bool del) {
  vec<ll> d(n + 1, LLONG_MAX);
  d[1] = 0;
  vec<ll> p(n + 1, -1);
  std::priority_queue<llPair, vec<llPair>, std::greater<llPair>> pq;
  pq.push({0, 1});

  while (!pq.empty()) {
    llPair top = pq.top();
    pq.pop();
    ll cur_weight = top.first;
    ll cur_node = top.second;

    if (cur_weight > d[cur_node]) {
      continue;
    }

    if(cur_node == n) {
      if (del) {
        int c = n;
        while (c != 1) {
          graph[p[c]][c] *= -1;
          c = p[c];
        }
        ll sec = dijkstra(false);
        c = n;
        while (c != 1) {
          graph[p[c]][c] *= -1;
          c = p[c];
        }
        if(sec == -1) {
          return -1;
        }
        return sec + d[n];
      }
      return d[n];
    }
    
    for (int i = 1; i <= n; i++) {
      if(graph[cur_node][i] > 0) {
        ll new_dist = d[cur_node] + graph[cur_node][i];
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

ll dijkstra_dijkstra() {
  vec<ll> d1(graph.size(), LLONG_MAX);
  vec<ll> d2(graph.size(), LLONG_MAX);

  vec<int> p1(graph.size(), -1);
  vec<int> p2(graph.size(), -1);

  std::priority_queue<QEntry, vec<QEntry>, GreaterWeight> pq1;
  std::priority_queue<QEntry, vec<QEntry>, GreaterWeight> pq2;

  graph[1][1] = 0;
  graph[0][1] = 0;

  pq1.push({1, 1, 0});
  pq2.push({0, 1, 0});

  while(!pq1.empty() || !pq2.empty()) {
    // pq1
    if(!pq1.empty()) {
      QEntry qe1 = pq1.top();
      pq1.pop();
      while (graph[qe1.from][qe1.to] == -1 && !pq1.empty()) {
        qe1 = pq1.top();
        pq1.pop();
      }
      if (graph[qe1.from][qe1.to] != -1 && d1[qe1.to] > qe1.weight) {
        graph[qe1.from][qe1.to] = -1;
        d1[qe1.to] = qe1.weight;
        p1[qe1.to] = qe1.from;
        if(qe1.to == n) {
          pq1 = std::priority_queue<QEntry, vec<QEntry>, GreaterWeight>();
        } else {
          for (int i = 1; i < graph.size(); i++) {
            if(graph[qe1.to][i] != -1) {
              ll new_weight = qe1.weight + graph[qe1.to][i];
              if (new_weight < d1[i]) {
                pq1.push({qe1.to, i, new_weight});
              }
            }
          }
        }
      }    
    }

    // pq2
    if(!pq2.empty()) {
      QEntry qe2 = pq2.top();
      pq2.pop();
      while (graph[qe2.from][qe2.to] == -1 && !pq2.empty()) {
        qe2 = pq2.top();
        pq2.pop();
      }
      if (graph[qe2.from][qe2.to] != -1 && d2[qe2.to] > qe2.weight) {
        graph[qe2.from][qe2.to] = -1;
        d2[qe2.to] = qe2.weight;
        p2[qe2.to] = qe2.from;

        if(qe2.to == n) {
          pq2 = std::priority_queue<QEntry, vec<QEntry>, GreaterWeight>();;
        } else {
          for (int i = 1; i < graph.size(); i++) {
            if(graph[qe2.to][i] != -1) {
              ll new_weight = qe2.weight + graph[qe2.to][i];
              if (new_weight < d2[i]) {
                pq2.push({qe2.to, i, new_weight});
              }
            }
          }
        }
      }    
    }
  }

  if(d1[n] == LLONG_MAX || d2[n] == LLONG_MAX) {
    return -1;
  }
  return d1[n] + d2[n];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>n>>m;

  graph = vec<vec<int>>(n + 1, vec<int>(n + 1, -1));

  while (m--) {
    ll a, b, c;
    std::cin>>a>>b>>c;
    graph[a][b] = c;
  }

  ll dij = dijkstra(true);
  if(dij == -1) {
    std::cout<<-1;
  } else {
    std::cout<<std::min(dij, dijkstra_dijkstra());
  }

  std::cout.flush();
}
