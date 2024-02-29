/**
 * Codeforces: https://codeforces.com/problemset/problem/228/E
 * 
 * Wiemy ze tak powstaly graf ma dwukierunkowe krawedzie zatem podzial na 
 * silnie spojne skladowe to po prostu podzial na skladowe.
 * Ponadto nie musimy sortowac grafu SCC topologicznie gdyz jest to graf bez krawedziowy
 * i kazda permutacja wierzcholkow jest poprawnym sortowaniem topologicznym
*/

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
  int scc; // indeks skladowej
  vec<int> rels;
};
vec<Node> graph;

bitset<207> vis;

void set_scc(int v, int scc) {
  if(vis[v]) return;
  vis[v] = true;
  graph[v].scc = scc;
  for(auto e : graph[v].rels) set_scc(e, scc);
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>m;
  graph = vec<Node>(2 * n + 1);
  while(m--) {
    int a, b, s;
    cin>>a>>b>>s;
    if(s == 1) {
      graph[a].rels.push_back(b);
      graph[n + a].rels.push_back(n + b);
      graph[b].rels.push_back(a);
      graph[n + b].rels.push_back(n + a);
    } else {
      graph[n + a].rels.push_back(b);
      graph[n + b].rels.push_back(a);
      graph[a].rels.push_back(n + b);
      graph[b].rels.push_back(n + a);
    }
  }

  int scc = 1;
  for(int i = 1; i <= 2 * n; i++) {
    if(vis[i]) continue;
    set_scc(i, scc++);
  }

  vec<int> ans;
  for(int i = 1; i <= n; i++) {
    if(graph[i].scc == graph[n + i].scc) {
      cout<<"Impossible";
      return 0;
    } else if(graph[i].scc < graph[n + i].scc) ans.push_back(i);
  }
  cout<<ans.size()<<"\n";
  for(auto a : ans) cout<<a<<" ";

  cout.flush();
}
