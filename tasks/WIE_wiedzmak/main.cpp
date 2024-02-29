#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

bool can_go(int path_mask, int sword_mask) { return (path_mask & sword_mask) == path_mask; }
int add_masks(int node_mask, int sword_mask) { return node_mask | sword_mask; }
struct Rel { int mask; int time; }; vec<Rel> rels;
struct QEntry {int v; int mask; int dist; };
struct GreaterQE { bool operator()(QEntry qe1, QEntry qe2) { return qe1.dist > qe2.dist; }; };
struct Node {
  int mask;
  vec<pair<int,int>> rels; // {dest, rid}
};

int n, m, p, k;
vec<Node> graph;


int bfs() {
  // [node][mask]
  vec<vec<int>> d(207, vec<int>(16390, INT_MAX));
  priority_queue<QEntry, vec<QEntry>, GreaterQE> pq; 
  pq.push({0, 0, 0}); // there is an edge from 0 to 1

  while(!pq.empty()) {
    auto [v, mask, dist] = pq.top();
    pq.pop();

    if(dist > d[v][mask]) continue;
    if(v == n) return d[v][mask];

    for(auto [w, rid] : graph[v].rels) {
      auto e = rels[rid];
      if(!can_go(e.mask, mask)) continue;
      int ndist = dist + e.time;
      int nmask = add_masks(graph[w].mask, mask);
      if(ndist < d[w][nmask]) {
        d[w][nmask] = ndist;
        pq.push({w, nmask, ndist});
      }
    }
  }

  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m>>p>>k;
  graph = vec<Node>(n + 1);
  for(int i = 0; i < k; i++) {
    int w, q, r;
    cin>>w>>q;
    while(q--) {
      cin>>r;
      graph[w].mask += 1 << r;
    }
  }

  rels.push_back({0, 0});
  graph[0].rels.push_back({1, 0});

  while(m--) {
    int a, b, t, c, mask = 0, u;
    cin>>a>>b>>t>>c;
    while(c--) {
      cin>>u;
      mask += 1 << u;
    }
    graph[a].rels.push_back({b, rels.size()});
    graph[b].rels.push_back({a, rels.size()});
    rels.push_back({mask, t});
  }

  cout<<bfs();

  cout.flush();
}