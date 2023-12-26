#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Node {
  // {dest, weight}
  vec<pair<int,int>> rels;
  vec<pair<int,int>> rev_rels;
};

vec<Node> graph;

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n, m;
  cin>>n>>m;
  graph = vec<Node>(n + 1);

  while(m--) {
    int a, b, c, d;
    cin>>a>>b>>c>>d;
    graph[a].rels.push_back({b, c});
    graph[b].rels.push_back({a, d});
    graph[b].rev_rels.push_back({a, c});
    graph[a].rev_rels.push_back({b, d});
  }

  // {dist, v}
  priority_queue<pair<int,int>, vec<pair<int,int>>, greater<pair<int,int>>> pq;

  vec<int> d(n + 1, INT_MAX - 10000);
  vec<int> p(n + 1, -1);
  d[1] = 0;
  p[1] = 1;
  for(auto [w, weight] : graph[1].rels) {
    d[w] = weight;
    p[w] = w;
    pq.push({weight, w});
  }

  while(!pq.empty()) {
    auto [dist, v] = pq.top();
    pq.pop();
    if(dist > d[v]) continue;

    for(auto [w, weight] : graph[v].rels) {
      int n_dist = dist + weight;
      if(n_dist < d[w]) {
        d[w] = n_dist;
        p[w] = p[v];
        pq.push({n_dist, w});
      }
    }
  }
  // czasami wystepuje mozliwosc ze istnieje tylko jeden zbior T 
  // wtedy wszystkie relacje v0 maja tego samego poprzednika dlatego na koncu trzeba odswiezyc poprzednikow
  // i ich dystansy bo edge casy moga popsuc wynik
  for(auto [w, weight] : graph[1].rels) {
    d[w] = weight;
    p[w] = w;
  }

  vec<int> h(n + 1, INT_MAX);
  pq.push({0, 1});
  h[1] = 0;

  while(!pq.empty()) {
    auto [dist, v] = pq.top();
    pq.pop();
    if(dist > h[v]) continue;

    for(auto [w, weight] : graph[v].rev_rels) {
      int n_dist = dist + weight;
      if(n_dist < h[w]) {
        h[w] = n_dist;
        pq.push({n_dist, w});
      }
    }
  }

  int min_c = INT_MAX;
  for(int v = 2; v < graph.size(); v++) {
    for(int w = 0; w < graph[v].rels.size(); w++) {
      if(p[v] != p[graph[v].rels[w].first] && graph[v].rels[w].first != 1) {
        min_c = min(min_c, graph[v].rels[w].second + d[v] + h[graph[v].rels[w].first]);
      }
    }
  }
  cout<<min_c;


  cout.flush();
}
