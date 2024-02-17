#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n, m;
vec<bool> visited;
vec<vec<int>> graph;

void bfs(int n) {
  queue<int> q;
  q.push(n);

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for(auto rel : graph[node]) {
      if(!visited[rel]) {
        visited[rel] = true;
        q.push(rel);
      }
    }
  }
  
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m;

  graph = vec<vec<int>>(n + 1);
  visited = vec<bool>(n + 1, false);
  
  while(m--) {
    int from, to;
    cin>>from>>to;
    graph[from].push_back(to);
    graph[to].push_back(from);
  }

  int c = 0;
  for(int i = 1; i <= n; i++) {
    if(!visited[i]) {
      bfs(i);
      c++;
    }
  }

  if(c == 1) {
    cout<<0;
  } else {
    cout<<1;
  }

  cout.flush();
}
