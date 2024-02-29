#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n;
vec<vec<int>> graph;
// vec<vec<int>> tgraph;
vec<bitset<1007>> used(1007); 
vec<int> we;
vec<int> wy;

bitset<1007> vis;
// 0 - unvisited, 1 - visited curr chain, 2 - visited somwhere in the past
vec<int> state;
vec<int> ans;
void dfs(int v) {
  if(vis[v]) return;
  vis[v] = true;
  for(auto e : graph[v]) dfs(e);
}
void bfs_byleco() {
  queue<int> q; q.push(1);
  while(!q.empty()) {
    auto v = q.front(); q.pop();

    for(auto e : graph[v]) {
      if(used[v][e]) continue;
      used[v][e] = true;
      q.push(e);
      ans.push_back(e);
      break;
    }
  }
}

bool dfs_cycle(int v) {
  if(state[v] == 1) return true;
  if(state[v] == 2) return false;
  bool ret = false;
  state[v] = 1;
  for(auto e : graph[v]) ret = ret || dfs_cycle(e);
  state[v] = 2;
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n;
  graph = vec<vec<int>>(n + 1);
  we = vec<int>(n + 1);
  wy = vec<int>(n + 1);
  state = vec<int>(n + 1);

  for(int i = 1, c, tmp; i <= n; i++) {
    cin>>c;
    while(c--) {
      cin>>tmp;
      graph[i].push_back(tmp);
      we[tmp]++;
      wy[i]++;
    }
  }

  bool exists = we[1] == wy[1] - 1 && we[n] == wy[n] + 1;
  for(int i = 2; i < n; i++) exists = exists && we[i] == wy[i];
  dfs(1);
  for(int i = 1; i <= n; i++) exists = exists && vis[i];

  // Wypisz byle jaka sciezke
  if(!exists) {
    bfs_byleco();
    for(auto a : ans) cout<<a<<" ";
    return 0;
  }
  vis.reset();
  state[n] = 2;
  if(dfs_cycle(1)) {
    // mozna
    // wypisz sciezke omijajac cykl

  } else {
    cout<<"NIE";
  }

  cout.flush();
}