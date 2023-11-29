#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct QEntry {
  int a;
  int b;
  int time;
};

struct Node {
  vec<int> rels;
};

vec<Node> graph;
vec<vec<bool>> was(251, vec<bool>(251, false));

int bfs(int a1, int a2) {
  std::queue<QEntry> q;
  q.push({a1, a2, 0});
  was[a1][a2] = true;
  while(!q.empty()) {
    auto [a, b, time] = q.front();
    q.pop();

    if(a == b) {
      return time;
    }
    time++;
    for(int i = 0; i < graph[a].rels.size(); i++) {
      for(int j = 0; j < graph[b].rels.size(); j++) {
        int n_a = graph[a].rels[i];
        int n_b = graph[b].rels[j];
        if(!was[n_a][n_b]) {
          q.push({n_a, n_b, time});
          was[n_a][n_b] = true;
        }
      }
    }
  }

  return -1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  int n, m;
  std::cin>>n>>m;

  graph = vec<Node>(n+1);
  
  int a, b;
  std::cin>>a>>b;

  while(m--) {
    int from, to;
    std::cin>>from>>to;
    graph[from].rels.push_back(to);
  }

  int res = bfs(a, b);
  if(res == -1) {
    std::cout<<"NIE";
  } else {
    std::cout<<res;
  }

  std::cout.flush();
}
