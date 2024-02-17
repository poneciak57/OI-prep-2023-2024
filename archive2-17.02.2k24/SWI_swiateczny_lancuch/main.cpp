#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Node {
  bool visited{false};
  vec<int> rels;
};

vec<Node> graph;

void dfs(ll cur) {
  if(graph[cur].visited) return;
  graph[cur].visited = true;

  for(auto r : graph[cur].rels) {
    dfs(r);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n, m;
  std::cin>>n>>m;

  graph = vec<Node>(n+1);

  while(m--) {
    ll a, b, l;
    std::cin>>a>>b>>l;
    for(int i = 0; i < l; i++) {
      graph[a + i].rels.push_back(b + i);
      graph[b + i].rels.push_back(a + i);
    }
  }

  ll count = 0;
  for(int i = 1; i < graph.size(); i++) {
    if(!graph[i].visited) {
      count++;
      dfs(i);
    }
  }
  std::cout<<count;

  std::cout.flush();
}