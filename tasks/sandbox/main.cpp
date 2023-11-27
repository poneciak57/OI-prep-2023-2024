#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;


vec<vec<int>> graph;
vec<int> can_reach;
vec<bool> visited;

void dfs(ll n) {
  if(visited[n]) return;

  visited[n] = true;
  can_reach.push_back(n);
  for(auto r : graph[n]) {
    dfs(r);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  ll n, m;
  std::cin>>n>>m;

  graph = vec<vec<int>>(n + 1);
  visited = vec<bool>(n + 1, false);

  while(m--) {
    int from, to;
    std::cin>>from>>to;
    graph[from].push_back(to);
    graph[to].push_back(from);
  }

  dfs(1);

  std::sort(can_reach.begin(), can_reach.end());

  std::cout<<can_reach.size()<<"\n";
  for(auto i : can_reach) {
    std::cout<<i<<" ";
  }
  

  std::cout.flush();
}
