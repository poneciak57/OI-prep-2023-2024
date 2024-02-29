#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n, m;

struct Node {
  int scc;
  int not_id;
  vec<int> rels;
  vec<int> rev_rels;
};

vec<Node> graph;
vec<vec<int>> scc_tgraph;
vec<int> scc_order;

stack<int> s;
bitset<32007> vis;
void dfs_order(int v) {
  if(vis[v]) return;
  vis[v] = true;
  for(auto e : graph[v].rels) dfs_order(e);
  s.push(v);
}

void dfs_set_scc(int v, int scc) {
  if(vis[v]) return;
  vis[v] = true;
  graph[v].scc = scc;
  for(auto e : graph[v].rev_rels) dfs_set_scc(e, scc);
}

void toposort_scc(int scc) {
  if(vis[scc]) return;
  vis[scc] = true;
  for(auto e : scc_tgraph[scc]) toposort_scc(e);
  s.push(scc);
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m;
  graph = vec<Node>(n * 4 + 1);
  for(int i = 1; i <= 2 * n; i++) graph[i].not_id = 2 * n + i;

  for(int i = 1; i <= 2 * n; i += 2) {
    // (i || i + 1)
    graph[2 * n + i].rels.push_back(i + 1);
    graph[i + 1].rev_rels.push_back(2 * n + i);
    graph[2 * n + i + 1].rels.push_back(i);
    graph[i].rev_rels.push_back(2 * n + i + 1);

    // (!i || ! i + 1)
    graph[i].rels.push_back(2 * n + i + 1);
    graph[2 * n + i + 1].rev_rels.push_back(i);
    graph[i + 1].rels.push_back(2 * n + i);
    graph[2 * n + i].rev_rels.push_back(i + 1);
  }

  while(m--) {
    int a, b;
    cin>>a>>b;
    graph[a].rels.push_back(2 * n + b);
    graph[2 * n + b].rev_rels.push_back(a);
    graph[b].rels.push_back(2 * n + a);
    graph[2 * n + a].rev_rels.push_back(b);
  }

  for(int i = 1; i <= 4 * n; i++) dfs_order(i);
  vis.reset();
  int scc = 1;
  while(!s.empty()) {
    auto v = s.top();
    s.pop();
    if(!vis[v]) {
      dfs_set_scc(v, scc);
      scc++;
    }
  }
  vis.reset();
  scc_tgraph = vec<vec<int>>(scc);
  scc_order = vec<int>(scc);

  for(int i = 1; i <= 4 * n; i++) {
    for(auto e : graph[i].rev_rels) {
      if(graph[e].scc != graph[i].scc) scc_tgraph[graph[i].scc].push_back(graph[e].scc);
    }
  }

  for(int i = 1; i < scc; i++) toposort_scc(i);
  vis.reset();
  int ind = 1;
  while(!s.empty()) {
    auto v = s.top();
    s.pop();
    scc_order[v] = ind++;
  }

  vec<int> ans;
  for(int i = 1; i <= 2 * n; i++) {
    int yes_ind = scc_order[graph[i].scc];
    int no_ind = scc_order[graph[n * 2 + i].scc];
    if(yes_ind == no_ind) {
      cout<<"NIE\n";
      return 0;
    } else if(yes_ind < no_ind) ans.push_back(i);
  }

  for(auto a : ans) {
    cout<<a<<"\n";
  }
  cout.flush();
}