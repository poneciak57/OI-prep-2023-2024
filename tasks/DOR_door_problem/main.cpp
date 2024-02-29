#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Node {
  int scc;
  vec<int> rels;
};
vec<Node> graph;

bitset<200007> vis;
void dfs(int v, int scc) {
  if(vis[v]) return;
  vis[v] = true;
  graph[v].scc = scc;
  for(auto e : graph[v].rels) dfs(e, scc);
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n, m;
  cin>>n>>m;
  vec<int> states(n + 1);
  vec<vec<int>> switches(n + 1);
  graph = vec<Node>(m * 2 + 1);

  for(int i = 1; i <= n; i++) cin>>states[i];
  for(int i = 1, c, tmp; i <= m; i++) {
    cin>>c;
    while(c--) {
      cin>>tmp;
      switches[tmp].push_back(i);
    } 
  }

  for(int i = 1; i <= n; i++) {
    int a = switches[i][0];
    int b = switches[i][1];
    if(states[i] != 0) {
      // none or both
      // (a || !b) && (b || !a)
      graph[m + a].rels.push_back(m + b);
      graph[b].rels.push_back(a);
      graph[m + b].rels.push_back(m + a);
      graph[a].rels.push_back(b);
    } else {
      // only one switch
      // (a || b) && (!a || !b)
      graph[m + a].rels.push_back(b);
      graph[m + b].rels.push_back(a);
      graph[a].rels.push_back(m + b);
      graph[b].rels.push_back(m + a);
    }
  }
  int scc = 1;
  for(int i = 1; i <= 2*m; i++) {
    if(vis[i]) continue;
    dfs(i, scc++);
  }
  for(int i = 1; i <= m; i++) {
    if(graph[i].scc == graph[m + i].scc) {
      cout<<"NO";
      return 0;
    }
  }
  cout<<"YES";
  cout.flush();
}