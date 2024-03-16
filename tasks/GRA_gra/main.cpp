#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

// aproach 2 podzadania

int n, m;
struct Rel { int dest; int color; ll cost {0}; };
struct Node {
  unordered_map<int, vec<int>> cs; // color rels
  unordered_map<int, ll> color_sum;
  unordered_map<int, ll> d { {0, LL_INF} };
  vec<Rel> rels;
};
vec<Node> graph;

struct QEntry { ll cost; int v; int e_color; ll e_cost; bool is_color {false}; };
struct QEG {
  bool operator()(QEntry &qe1, QEntry &qe2) {
    return qe1.cost > qe2.cost;
  }
};

ll dijkstra() {
  graph[1].d[0] = 0;
  // {cost, {v, rr}}
  priority_queue<QEntry,vec<QEntry>, QEG> pq;
  pq.push({0, 1, 0, 0});

  while(!pq.empty()) {
    auto [cost, v, e_color, e_cost, is_color] = pq.top();
    pq.pop();
    
    // cout<<"v: "<<v<<" cost: "<<cost<<" e_cost: "<<e_cost<<" e_color: "<<e_color<<" is_color: "<<is_color<<"\n";
    // cout<<graph[v].color_sum[16]<<"\n";
    if(v == n) return cost;

    if(!is_color) {
      if(cost > graph[v].d[0]) continue;
      // wszystkie krawedzie
      for(auto [e, col, c] : graph[v].rels) {
        ll nc = min(cost + c, cost + graph[v].color_sum[col] - c);
        ll d_ov = graph[e].d[0];
        ll d_col = graph[e].d[col];

        if(nc < d_ov) {
          // dodajemy ogolnie
          graph[e].d[0] = nc;
          pq.push({nc, e, col, c, false});
        }

        if(cost < d_col) {
          // dodajemy jako kolor
          graph[e].d[col] = cost;
          pq.push({cost + c, e, col, c, true});
        }
      }

    } else {
      if((cost - e_cost) > graph[v].d[e_color]) continue;
      // jeden kolor
      ll sum = graph[v].color_sum[e_color];
      for(auto rid : graph[v].cs[e_color]) {
        auto &[e, col, c] = graph[v].rels[rid];
        ll nc = cost + sum - c - e_cost;
        if(nc < graph[e].d[0]) {
          graph[e].d[0] = nc;
          pq.push({nc, e, col, c, false});
        }
      }
    }
  }

  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m;
  graph = vec<Node>(n + 1);
  while(m--) {
    int a, b, c;
    ll p;
    cin>>a>>b>>c>>p;
    graph[a].rels.push_back({b, c, p});
    graph[b].rels.push_back({a, c, p});
    graph[a].color_sum[c] += p;
    graph[b].color_sum[c] += p;
    graph[a].d[c] = LL_INF;
    graph[b].d[c] = LL_INF;
    graph[a].cs[c].push_back(graph[a].rels.size() - 1);
    graph[b].cs[c].push_back(graph[b].rels.size() - 1);
  }

  // cout<<graph.size();
  // for(int i = 1; i <= n; i++) {
  //   cout<<"node: "<<i<<"\n";
  //   for(auto [w, col, cost] : graph[i].rels) {
  //     cout<<w<<" cost: "<<cost<<"\n";
  //   }
  // }
  
  std::cout<<dijkstra();

  std::cout.flush();
}