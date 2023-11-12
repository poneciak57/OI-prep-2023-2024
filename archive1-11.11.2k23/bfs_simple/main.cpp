#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Node {
  int dist{-1};
  vec<int> rels;
};

vec<Node> graf;

void bfs() {
  // {nid, dist}
  std::queue<std::pair<int, int>> q;
  q.push({1, 0});

  while(!q.empty()) {
    auto [node_id, dist] = q.front();
    q.pop();

    if(graf[node_id].dist != -1) {
      continue;
    }

    graf[node_id].dist = dist;
    int new_dist = dist + 1;

    for(auto r : graf[node_id].rels) {
      q.push({r, new_dist});
    }
    
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n, m;
  std::cin>>n>>m;

  graf = vec<Node>(n + 1);

  while(m--) {
    int from, to;
    std::cin>>from>>to;
    graf[from].rels.push_back(to);
    graf[to].rels.push_back(from);
  }

  bfs();

  for(int i = 1; i < graf.size(); i++) {
    std::cout<<graf[i].dist<<" ";
  }

  std::cout.flush();
}
