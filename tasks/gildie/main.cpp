#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

struct Node {
  char c { 'N' };
  vec<ll> rels;
};

vec<Node> graph;
vec<bool> visited;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  

  ll n, m;
  std::cin>>n>>m;
  graph = vec<Node>(n + 1); 
  visited = vec<bool>(n + 1, false);


  while (m--) {
    ll from, to;
    std::cin>>from>>to;
    graph[from].rels.push_back(to);
    graph[to].rels.push_back(from);
  }


  std::cout.flush();
}
