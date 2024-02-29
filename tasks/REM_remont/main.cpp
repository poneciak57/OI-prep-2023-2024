#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n, k, t;

struct Node {
  int scc {-1};
  vec<int> rels;
  vec<int> trels;
};
vec<Node> graph;

ll get_hash(ll f, ll s) { return f * (k + 1) + s; };

bitset<600007> vis;
stack<int> s;
void get_order(int v) {
  if(vis[v]) return;
  vis[v] = true;
  for(auto e : graph[v].rels) get_order(e);
  s.push(v);
}

void set_scc(int v, int scc) {
  if(graph[v].scc != -1) return;
  graph[v].scc = scc;
  for(auto e : graph[v].trels) set_scc(e, scc);
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>t;
  while(t--) {
    cin>>n>>k;
    vec<int> inp(n); 
    for(int i = 0; i < n; i++) cin>>inp[i];
    // [0..n] - wierzcholki tak
    // [n..2n] - wierzcholki nie
    // [2n..3n] - wierzcholki zasiegowe tak
    // [3n..4n] - wierzcholki zasiegowe nie
    graph = vec<Node>(4*n);
    vis.reset();
    unordered_map<ll, int> lri; // last range index
    lri[get_hash(inp[0], inp[1])] = 1;

    // !a(0) || p(0)
    graph[0].rels.push_back(2 * n);
    graph[3 * n].rels.push_back(n);
    graph[2 * n].trels.push_back(0);
    graph[n].trels.push_back(3 * n);

    for(int i = 1; i < n - 1; i++) {
      ll h = get_hash(inp[i], inp[i + 1]);

      // a(i-1) || a(i)
      graph[i - 1 + n].rels.push_back(i);
      graph[i + n].rels.push_back(i - 1);
      graph[i].trels.push_back(i - 1 + n);
      graph[i - 1].trels.push_back(i + n);

      if(lri[h] != NULL) {
        int last_oc = lri[h] - 1;

        // !p(i - 1) || p(i)
        // cout<<"i: "<<i<<" last_oc: "<< last_oc<<'\n';
        graph[last_oc + 2 * n].rels.push_back(i + 2 * n);
        graph[i + 3 * n].rels.push_back(last_oc + 3 * n);
        graph[i + 2 * n].trels.push_back(last_oc + 2 * n);
        graph[last_oc + 3 * n].trels.push_back(i + 3 * n);

        // !p(i - 1) || !a(i)
        graph[last_oc + 2 * n].rels.push_back(i + n);
        graph[i].rels.push_back(last_oc + 3 * n);
        graph[i + n].trels.push_back(last_oc + 2 * n);
        graph[last_oc + 3 * n].trels.push_back(i);
      }
      // !a(i) || p(i)
      graph[i].rels.push_back(i + 2 * n);
      graph[i + 3 * n].rels.push_back(i + n);
      graph[i + 2 * n].trels.push_back(i);
      graph[i + n].trels.push_back(i + 3 * n);
      lri[h] = i + 1;
    }
    // lasts are always on
    graph[0 + n].rels.push_back(0);
    graph[n - 2 + n].rels.push_back(n - 2);
    graph[0].trels.push_back(0 + n);
    graph[n - 2].trels.push_back(n - 2 + n);


    for(int i = 0; i < 4 * n; i++) get_order(i);
    int scc = 0;
    while(!s.empty()) {
      auto next = s.top(); s.pop();
      if(graph[next].scc != -1) continue;
      set_scc(next, scc++);
    }
    bool ok = true;
    for(int i = 0; i < n; i++) ok = ok && (graph[i].scc != graph[i + n].scc);
    for(int i = 2 * n; i < 3 * n; i++) ok = ok && (graph[i].scc != graph[i + n].scc);
    if(ok) cout<<"TAK\n";
    else cout<<"NIE\n";
  }

  cout.flush();
}