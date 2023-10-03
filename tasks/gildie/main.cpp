#include <bits/stdc++.h>
#include <iostream>
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

void dfs(ll n, char c) {
  visited[n] = true;
  graph[n].c = c;
  for (ll r : graph[n].rels) {
    if (!visited[r]) {
      char c_n = (c == 'K' ? 'S' : 'K');
      dfs(r, c_n);
    }
  }
}

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
  
  graph[0].rels.push_back(1);
  for (Node n : graph) {
    if(n.rels.empty()) {
      std::cout<<"NIE";
      return 0;
    }
  }
  std::cout<<"TAK"<<"\n";
  for (ll i = 1; i < visited.size(); i++) {
    if(!visited[i]) {
      dfs(i, 'K');
    }
    std::cout<<graph[i].c<<"\n";
  } 

  std::cout.flush();
}
