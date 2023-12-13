#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n, m, A, B, C;

vec<vec<int>> graph;

int get_dist(int from, int to) {
  // {node, dist}
  queue<pair<int, int>> q;
  q.push({from, 0});

  vec<bool> visited(n + 1, false);

  while(!q.empty()) {
    auto [node, dist] = q.front();
    q.pop();

    if(node == to) return dist;

    for(auto rel : graph[node]) {
      if(!visited[rel]) {
        q.push({rel, dist + 1});
        visited[rel] = true;
      }
    }
  }

  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m;
  graph = vec<vec<int>>(n + 1);

  while(m--) {
    int t1, t2;
    cin>>t1>>t2;
    graph[t1].push_back(t2);
    graph[t2].push_back(t1);
  }

  cin>>A>>B>>C;

  if(get_dist(A, B) == (get_dist(A, C) + get_dist(C, B))) {
    cout<<"TAK";
  } else {
    cout<<"NIE";
  }

  cout.flush();
}
