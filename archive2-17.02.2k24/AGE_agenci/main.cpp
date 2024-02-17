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
  bool prim;
};

struct Node {
  vec<int> rels;
};

vec<Node> graph;
vec<vec<vec<bool>>> was(251, vec<vec<bool>>(251, vec<bool>(2, false)));

int bfs(int a1, int a2) {
  std::queue<QEntry> q;
  q.push({a1, a2, 0, false});
  was[a1][a2][0] = true;
  while(!q.empty()) {
    auto [a, b, time, b_turn] = q.front();
    q.pop();

    time++;
    bool not_b_turn = !b_turn;
    if(b_turn) {
      for(int i = 0; i < graph[b].rels.size(); i++) {
        int n_b = graph[b].rels[i];
        if(!was[a][n_b][not_b_turn]) {
            q.push({a, n_b, time, not_b_turn});
            was[a][n_b][not_b_turn] = true;
        }
      }
    } else {
      if(a == b) {
        return (time-1)/2;
      }
      for(int i = 0; i < graph[a].rels.size(); i++) {
        int n_a = graph[a].rels[i];
        if(!was[n_a][b][not_b_turn]) {
            q.push({n_a, b, time, not_b_turn});
            was[n_a][b][not_b_turn] = true;
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
