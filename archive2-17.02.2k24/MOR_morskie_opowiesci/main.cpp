#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Q {
  int ind;
  int from;
  int to;
  int dist;
  bool is_possible;
};

struct QEntry {
  int node;
  bool is_odd;
  int dist;
};

struct Node {
  vec<int> rels;
};

int n;
vec<vec<int>> dists;
vec<Node> graph;

void bfs(int start) {
  // [is_odd][node_id]
  dists = vec<vec<int>>(2, vec<int>(n + 1, -1));
  // {node, odd}
  std::queue<QEntry> q;
  q.push({start, false, 0});
  dists[0][start] = 0;

  while (!q.empty())
  {
    auto [node, is_odd, dist] = q.front();
    q.pop();

    int n_dist = dist + 1;
    bool n_is_odd = !is_odd;

    for(auto rel : graph[node].rels) {
      if(dists[n_is_odd][rel] == -1) {
        dists[n_is_odd][rel] = n_dist;
        q.push({rel, n_is_odd, n_dist});
      }
    }
  }
  
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int m, k;
  std::cin>>n>>m>>k;
  graph = vec<Node>(n + 1);

  while (m--)
  {
    int a, b;
    std::cin>>a>>b;
    graph[a].rels.push_back(b);
    graph[b].rels.push_back(a);
  }
  
  vec<Q> qs(k);
  for(int i = 0; i < k; i++) {
    int a, b, c;
    std::cin>>a>>b>>c;
    qs[i] = {i, a, b, c};
  }
  
  std::sort(qs.begin(), qs.end(), [](Q &q1, Q &q2) { return q1.from < q2.from; });
  
  int last_from = -1;
  for(auto &q : qs) {
    if(last_from != q.from) {
      bfs(q.from);
      last_from = q.from;
      // std::cout<<"bfs for: "<<last_from<<"\n";
    }
    int dist_mod = q.dist % 2;
    q.is_possible = (dists[dist_mod][q.to] != -1) && (dists[dist_mod][q.to] <= q.dist) && (graph[q.from].rels.size() > 0);
    // std::cout<<"set qpossible: "<< q.is_possible<<"\n";
  }
  
  std::sort(qs.begin(), qs.end(), [](Q &q1, Q &q2) { return q1.ind < q2.ind; });

  for(auto q : qs) {
    if(q.is_possible) {
      std::cout<<"TAK\n";
    } else {
      std::cout<<"NIE\n";
    }
  }

  std::cout.flush();
}
