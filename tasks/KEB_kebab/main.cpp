#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int N = 1;
struct Node {
  // {v, dist}
  vec<pair<int,int>> rels;

  int range;
  int answer { 0 };

  int subt_size;
  bool was_centroid { false };
};
vec<Node> graph;

int subt_size(int v, int p) {
  graph[v].subt_size = 1;
  for(auto [e, d] : graph[v].rels) {
    if(e == p || graph[e].was_centroid) continue;
    graph[v].subt_size += subt_size(e, v);
  }
  return graph[v].subt_size;
}

int find_centroid(int v, int tsize, int p) {
  for(auto [e, d] : graph[v].rels) {
    if(e == p || graph[e].was_centroid) continue;
    if(graph[e].subt_size * 2 > tsize) return find_centroid(e, tsize, v);
  }
  return v;
}

// {v, dist}
vec<int> dists;
vec<vec<pair<int,int>>> groups;

void dfs_set(int v, int dist, int centroid_child, int p) {
  groups[centroid_child].push_back({v, dist});
  dists.push_back(dist);
  for(auto [e, d] : graph[v].rels) {
    if(e == p || graph[e].was_centroid) continue;
    dfs_set(e, dist + d, centroid_child, v);
  }
}


void centroid_decomp(int v) {
  int tsize = subt_size(v, v);
  int centroid = find_centroid(v, tsize, v);

  groups = vec<vec<pair<int,int>>>(graph[centroid].rels.size());
  dists.clear();
  dists.push_back(0);
  for(int i = 0; i < graph[centroid].rels.size(); i++) {
    groups[i].clear();
    auto [e, d] = graph[centroid].rels[i];
    if(graph[e].was_centroid) continue;
    dfs_set(e, d, i, centroid);
  }
  sort(dists.begin(), dists.end());
  for(int i = 0; i < groups.size(); i++) {
    vec<int> gdists;
    auto &group = groups[i];
    for(auto [v, d] : group) gdists.push_back(d);
    sort(gdists.begin(), gdists.end());
    for(auto [v, d] : group) {
      int ddist = graph[v].range - d;
      if(ddist < 0) continue;
      auto ub = upper_bound(dists.begin(), dists.end(), ddist);
      auto ubg = upper_bound(gdists.begin(), gdists.end(), ddist);
      graph[v].answer += (ub - dists.begin()) - (ubg - gdists.begin());
    }
  }
  
  auto ub = upper_bound(dists.begin(), dists.end(), graph[centroid].range);
  graph[centroid].answer += (ub - dists.begin());

  graph[centroid].was_centroid = true;
  for(auto [e, d] : graph[centroid].rels) {
    if(graph[e].was_centroid) continue;
    centroid_decomp(e);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n;
  cin>>n;
  graph = vec<Node>(n);
  for(int i = 0; i < n; i++) cin>>graph[i].range;
  for(int i = 1; i < n; i++) {
    int a, b, d;
    cin>>a>>b>>d; --a; --b;
    graph[a].rels.push_back({b, d});
    graph[b].rels.push_back({a, d});
  }

  centroid_decomp(0);

  for(int i = 0; i < n; i++) cout<<graph[i].answer<<"\n";

  cout.flush();
}