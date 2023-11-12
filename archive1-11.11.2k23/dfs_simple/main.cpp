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
vec<bool> visited;
vec<int> can_reach;

void dfs(int n) {
  visited[n] = true;
  can_reach.push_back(n);

  for(auto r : graf[n].rels) {
    if(!visited[r]) {
      dfs(r);
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
  visited = vec<bool> (n + 1, false);
  while(m--) {
    int from, to;
    std::cin>>from>>to;
    graf[from].rels.push_back(to);
    graf[to].rels.push_back(from);
  }

  dfs(1);

  std::cout<<can_reach.size()<<"\n";
  for(auto cr : can_reach) {
    std::cout<<cr<<" ";
  }

  std::cout.flush();
}
