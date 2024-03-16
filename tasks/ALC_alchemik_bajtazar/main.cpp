#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

/**
 * G - graf startowy
 * H - graf ktory mamy uzyskac
 * 
 * s_edges - krawedzie startowe
 * e_edges - krawedzie koncowe
 * 
*/

int root = 1, n;
vec<vec<int>> G;
vec<vec<int>> H;
vec<pair<int, int>> s_edges;
vec<pair<int, int>> e_edges;

bitset<30007> vis;
// {root_dist, node}
vec<pair<int,int>> dists;

int bfs_G() {
  // {dist, v}
  queue<pair<int,int>> q;
  vis.reset();
  dists.clear();
  vis[root] = true;
  q.push({0, root});
  while(!q.empty()) {
    auto [d, v] = q.front();
    q.pop();

    dists.push_back({d, v});
    for(auto e : G[v]) {
      if(!vis[e]) {
        vis[e] = true;
        q.push({d + 1, e});
      }
    }
  }
  sort(dists.begin(), dists.end());
  int dind = 0;
  while(dind <= n && dists[dind].first <= 1) dind++;
  return dind;
}

int bfs_H() {
  // {dist, v}
  queue<pair<int,int>> q;
  vis.reset();
  dists.clear();
  vis[root] = true;
  q.push({0, root});
  while(!q.empty()) {
    auto [d, v] = q.front();
    q.pop();

    dists.push_back({d, v});
    for(auto e : H[v]) {
      if(!vis[e]) {
        vis[e] = true;
        q.push({d + 1, e});
      }
    }
  }
  sort(dists.begin(), dists.end(), [](pair<int,int> p1, pair<int,int> p2) { return p1.first > p2.first; });
  return 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int m;
  cin>>n>>m;
  G = vec<vec<int>>(n + 1);
  H = vec<vec<int>>(n + 1);
  while(m--) {
    int a, b;
    cin>>a>>b;
    G[a].push_back(b);
    G[b].push_back(a);
    s_edges.push_back({a, b});
  }
  cin>>m;
  while(m--) {
    int a, b;
    cin>>a>>b;
    H[a].push_back(b);
    H[b].push_back(a);
    e_edges.push_back({a, b});
  }

  struct ANS { char op; int a; int b; };
  vec<ANS> ans;

  // laczymy wszystkie wierzcholki z korzeniem gwiazdy
  int di = bfs_G();
  for(int i = di; i < dists.size(); i++) {
    ans.push_back({'+', dists[i].second, root});
  }

  // usuwamy wszystkie krawedzie nielaczace z korzeniem
  for(auto [a, b] : s_edges) {
    if(a == root || b == root) continue;
    ans.push_back({'-', a, b});
  }

  // dodajemy krawedzie potrzebne aby graf sie zgadzal
  for(auto [a, b] : e_edges) {
    if(a == root || b == root) continue;
    ans.push_back({'+', a, b});
  }

  // usuwamy niepotrzebne laczenia z korzeniem
  di = bfs_H();
  while(dists[di].first > 1) {
    ans.push_back({'-', root, dists[di].second});
    di++;
  }

  cout<<ans.size()<<"\n";
  for(auto [op, a, b] : ans) cout<<op<<" "<<a<<" "<<b<<"\n";

  cout.flush();
}