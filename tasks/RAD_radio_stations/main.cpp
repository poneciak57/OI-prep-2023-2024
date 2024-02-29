#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const int LIM = 4 * 1e5 * 4 + 7;

int n, p, M, m;
struct Node { int scc {-1}; vec<int> rels; vec<int> trels; };
vec<Node> graph;
vec<vec<int>> scc_tgraph;
vec<int> scc_ind;

stack<int> ord;
bitset<LIM> vis;
void get_ord(int v) {
  vis[v] = true;
  for(auto e : graph[v].rels) if(!vis[e]) get_ord(e);
  ord.push(v);
}
void set_scc(int v, int scc) {
  graph[v].scc = scc;
  for(auto e : graph[v].trels) if(graph[e].scc == -1) set_scc(e, scc); 
}
void toposort(int v) {
  vis[v] = true;
  for(auto e : scc_tgraph[v]) if(!vis[e]) toposort(e);
  ord.push(v);
}

int main() {
  ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>p>>M>>m;
  graph = vec<Node>(2 * p + 1 + 2 * M + 1);

  // i + 1 => i
  // !i => !i + 1
  for(int i = 2 * p + 1; i < 2 * p + 1 + M - 1; i++) {
    graph[i + 1].rels.push_back(i);
    graph[i].trels.push_back(i + 1);
    graph[i + M].rels.push_back(i + M + 1);
    graph[i + M + 1].trels.push_back(i + M);
  }
  
  for(int i = 0, x, y; i < n; i++) {
    cin>>x>>y;
    // x || y
    graph[x + p].rels.push_back(y);
    graph[y + p].rels.push_back(x);
    graph[y].trels.push_back(x + p);
    graph[x].trels.push_back(y + p);
  }
  
  for(int i = 1, l, r; i <= p; i++) {
    cin>>l>>r;
    // ai => l
    // !l => !ai
    graph[i].rels.push_back(2*p + l);
    graph[2 * p + M + l].rels.push_back(p + i);
    graph[2*p + l].trels.push_back(i);
    graph[p + i].trels.push_back(2 * p + M + l);

    // ai => !r + 1
    // r + 1 => !ai
    if(r >= M) continue;
    graph[i].rels.push_back(2 * p + M + r + 1);
    graph[2 * p + r + 1].rels.push_back(p + i);
    graph[2 * p + M + r + 1].trels.push_back(i);
    graph[p + i].trels.push_back(2 * p + r + 1);
  }

  for(int i = 0, u, v; i < m; i++) {
    cin>>u>>v;
    // !u || !v
    graph[u].rels.push_back(p + v);
    graph[v].rels.push_back(p + u);
    graph[p + v].trels.push_back(u);
    graph[p + u].trels.push_back(v);
  }
  
  for(int i = 1; i < graph.size(); i++) {
    if(!vis[i]) get_ord(i);
  }

  int scc = 0;
  while(!ord.empty()) {
    auto next = ord.top(); ord.pop();
    if(graph[next].scc == -1) set_scc(next, scc++);
  }

  scc_tgraph = vec<vec<int>>(scc);
  scc_ind = vec<int>(scc);
  for(int i = 1; i < graph.size(); i++) {
    for(auto e : graph[i].trels) {
      if(graph[i].scc != graph[e].scc) {
        // cout<<graph[i].scc<<" "<<graph[e].scc<<endl;
        scc_tgraph[graph[i].scc].push_back(graph[e].scc);
      }
    }
  }
  vis.reset();
  for(int i = 0; i < scc; i++) if(!vis[i]) toposort(i);
  int ind = 0;
  while(!ord.empty()) {
    auto cur = ord.top(); ord.pop();
    scc_ind[cur] = ind++;
  }

  int max_signal = 0;
  vec<int> stations;
  for(int i = 1; i < p + 1; i++) {
    int iy = scc_ind[graph[i].scc];
    int in = scc_ind[graph[i + p].scc];
    if(iy == in) {
      cout<<-1;
      return 0;
    } else if(iy < in) stations.push_back(i);
  }
  for(int i = 2 * p + 1; i < 2 * p + 1 + M; i++) {
    int iy = scc_ind[graph[i].scc];
    int in = scc_ind[graph[i + M].scc];
    if(iy == in) {
      cout<<-1;
      return 0;
    } else if(iy < in) max_signal = i - (2 * p);
    else break;
  }

  cout<<stations.size()<<" "<<max_signal<<"\n";
  for(auto s : stations) cout<<s<<" ";
  std::cout.flush();
}