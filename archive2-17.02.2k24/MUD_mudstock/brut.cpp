#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Rel {
  int dest;
  int dist;
};

struct Node {
  vec<Rel> rels;
  int value;
  int n;
  int k;
};

vec<Node> graph;

vec<bool> visited;

int sum = 0;

void dfs(int n, int dist) {
  if(visited[n]) {
    return;
  }
  visited[n] = true;
  sum += dist * graph[n].value;
  for(auto r: graph[n].rels) {
    dfs(r.dest, r.dist + dist);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n, stolica_count;
  std::cin>>n>>stolica_count;

  graph.push_back({{},stolica_count, 0, 0});

  // wczytanie danych kolei i obliczenie wyników dla festivalu w stolicy
  for(int i = 0, dist, count; i < n; i++) {
    int k;
    std::cin>>k;


    int prev = 0;

    for(int j = 0; j < k; j++) {
      std::cin>>dist>>count;
      graph.push_back({{{prev, dist}}, count, j + 1, i + 1});
      graph[prev].rels.push_back({(int)(graph.size() - 1), dist});
      prev = graph.size() - 1;
    }
    
  }

  int min_dist = INT_MAX;
  int min_n, min_k;
  for(int i = 0; i < graph.size(); i++) {
    visited = vec<bool>(graph.size() + 7, false);
    sum = 0;
    dfs(i, 0);
    if(sum < min_dist) {
      min_dist = sum;
      min_n = graph[i].n;
      min_k = graph[i].k;
    }
  }

  std::cout<<min_dist<<"\n";
  std::cout<<min_k<<" "<<min_n<<"\n";
  

  std::cout.flush();
}
