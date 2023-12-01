#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

int dest_n;

struct Rel {
  int dest;
  int cost{0};
};

struct Node {
  vec<Rel> rels;
};

vec<Node> graph;
// [node][money]
vec<vec<bool>> visited;

void bfs(int start_node, int start_money) {
  // {node, money}
  std::queue<std::pair<int, int>> q;
  visited[start_node][start_money] = true;
  q.push({start_node, start_money});

  while (!q.empty())
  {
    auto [node, money] = q.front();
    q.pop();

    for(auto [dest, cost] : graph[node].rels) {
      int new_cost = money - cost;
      if(new_cost >= 0 && !visited[dest][new_cost]) {
        visited[dest][new_cost] = true;
        q.push({dest, new_cost});
      }
    }
  }
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n, m;
  std::cin>>n>>dest_n;

  graph = vec<Node>(n+1);
  visited = vec<vec<bool>>(n + 1, vec<bool>(2001, false));

  std::cin>>m;
  while(m--) {
    int from, to;
    std::cin>>from>>to;
    graph[from].rels.push_back({to});
  }

  std::cin>>m;
  while(m--) {
    int from, to, cost;
    std::cin>>from>>to>>cost;
    graph[from].rels.push_back({to, cost});
  }

  int start, money;
  std::cin>>start>>money;
  bfs(start, money);
  int min_money = INT_MAX;
  for(int i = 0; i <= dest_n; i++) {
    int j = 0;
    while(j < 2001 && !visited[i][j]) {
      j++;
    }
    min_money = std::min(min_money, j);
  }
  std::cout<<min_money;

  std::cout.flush();
}
