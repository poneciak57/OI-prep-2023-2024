#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<int, int> iPair;

template <typename T>
using vec = std::vector<T>;

vec<vec<int>> graph;

struct QEntry {
  int dist;
  int node;
  int trans;
};

struct GreaterHeight {
  bool operator()(QEntry const& qe1, QEntry const& qe2) {
    return qe1.dist > qe2.dist;
  }
};


int dijkstra(int src, int dest) {
  vec<int> d(graph.size(), INT_MAX);
  d[src] = 0;
  
  vec<int> trans(graph.size(), -1);
  std::priority_queue<QEntry, vec<QEntry>, GreaterHeight> pq;
  pq.push({0, src, -1});

  while (!pq.empty()) {
    QEntry e = pq.top();
    pq.pop();

    if(e.node == dest) {
      return d[dest];
    }

    if(e.dist > d[e.node]) {
      continue;
    }

    for(int i = 0; i < graph.size(); i++) {
      if(graph[i][e.node] != 0 && graph[i][e.node] != e.trans) {
        int new_dist = e.dist + graph[i][e.node];
        if(new_dist < d[i]) {
          d[i] = new_dist;
          pq.push({new_dist, i, graph[i][e.node]});
        }
      }
    }
  }

  return -1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n, a, b;
  std::cin>>n>>a>>b;
  graph = vec<vec<int>>(n, vec<int>(n, 0));

  int d;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin>>d;
      graph[i][j] = d;
    }
  }

  std::cout<<dijkstra(a, b);


  std::cout.flush();
}
