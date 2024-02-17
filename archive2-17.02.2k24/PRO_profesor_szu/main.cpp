#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1000992299;

ll powm(ll a, ll n, ll MOD);
ll multm(ll a, ll b, ll MOD);
ll divm(ll a, ll b, ll MOD);

inline int rand_range(int from, int to) {
  return (rand() % (to - from + 1)) + from;
}

/**
 * Jesli graf posiada cykl z ktorego jest dojscie do gmachu to odpowiedzia bedzie "zawsze"
 * i wszystkie wierzcholki z SSC ktore maja dojscie do gmachu
 * 
 * dojscie do gmachu mozna sprawdzic uzywajac bfs lub dfs na transponowanym grafie SSC zaczynajac od n
 * 
 * jesli nie istnieje cykl z ktorego jest dojscie to aby uzyskac odpowiedz trzeba topologicznie posortowac graf SSC
 * (wystarczy tylko skladowa tego grafu ktora ma w sobie gmach)
 * i wykonac w takiej kolejnosci dynamika
 * 
 * ew zaczac od gmachu i na transponowanym grafie SSC isc od niego i dodawac ilosc mozliwosci
 * 
 * !!!
 * Jesli gmach lezy w SCC ktory jest > 1 elementowy to kazda nawet jednoelementowa skladowa moze osiagnac wartosc "zawsze" krazac dookola gmachu
*/

struct Node {
  int scc {-1};
  vec<int> rels;
};

struct CNode {
  int c {0}; // wielkosc skladowej
  int pb {0}; // mozliwosci dojscia z danego wierzcholka do gmachu
  vec<int> rels;
  // vec<int> nodes;
};

vec<Node> graph;
vec<vec<int>> trans_graph;
// vec<CNode> c_graph;
vec<CNode> c_trans_graph;



stack<int> order;
vec<bool> visited;

void get_order(int v) {
  if(visited[v]) return;
  visited[v] = true;

  for(auto e : graph[v].rels) {
    get_order(e);
  }
  order.push(v);
}

void set_scc(int v, int scc) {
  if(graph[v].scc != -1) return;
  graph[v].scc = scc;
  c_trans_graph[scc].c++;
  // c_trans_graph[scc].nodes.push_back(v);
  for(auto e : trans_graph[v]) {
    set_scc(e, scc);
  }
}

stack<pair<int, int>> order2;

void toposort_scc(int v, bool does_prev_have_cycle) {
  if(visited[v]) return;
  visited[v] = true;

  for(auto e : c_trans_graph[v].rels) {
    toposort_scc(e, does_prev_have_cycle || (c_trans_graph[v].c > 1));
  }
  order2.push({v, does_prev_have_cycle || (c_trans_graph[v].c > 1)});
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  int n, m;
  cin>>n>>m;
  n += 1;
  graph = vec<Node>(n + 1);
  trans_graph = vec<vec<int>>(n + 1);
  visited = vec<bool>(n + 1, false);

  while(m--) {
    int a, b;
    cin>>a>>b;
    graph[a].rels.emplace_back(b);
    trans_graph[b].emplace_back(a);
  }

  for(int i = 1; i <= n; i++) {
    get_order(i);
  }

  int scc = 0;
  while(!order.empty()) {
    auto top = order.top();
    order.pop();
    if(graph[top].scc == -1) {
      c_trans_graph.push_back({});
      set_scc(top, scc++);
    }
  }

  // ustwwiamy relacje w transponowanym grafie spojnych skladowych
  for(int i = 1; i <= n; i++) {
    for(auto e : graph[i].rels) {
      if(graph[e].scc != graph[i].scc) {
        // jest transponowany relacje sa odwrotne
        c_trans_graph[graph[e].scc].rels.push_back(graph[i].scc);
      }
    }
  }

  // jesli gmach lezy w skladowej skladajacej sie z wiecej niz jednego wierzcholka
  bool gmach_in_cycle = c_trans_graph[graph[n].scc].c > 1;

  visited = vec<bool>(scc + 1, false);

  // tutaj musimy rozwazyc dwie opcje
    // 1. istnieje rozwiazanie zawsze jakas skladowa scc.c > 1 prowadzi do gmachu
    // 2. taka skladowa nie istnieje i rozwiazanie musimy obliczyc dynamicznie

    // musimy posortowac topologicznie graf skladowych i wykonac proste programowanie dynamiczne
  toposort_scc(graph[n].scc, false);

  vec<int> res;
  visited = vec<bool>(scc + 1, false);
  int cur_max = 0;
  c_trans_graph[graph[n].scc].pb = 1;
  while(!order2.empty()) {
    auto [v, has_cycles] = order2.top();
    order2.pop();
    if(has_cycles) {
      c_trans_graph[v].pb = INT_MAX;
      if(cur_max != INT_MAX) res.clear();
      cur_max = INT_MAX;
      res.push_back(v);

    } else {
      if(c_trans_graph[v].pb > cur_max && cur_max <= 36500) {
        res.clear();
        cur_max = c_trans_graph[v].pb;
      }
      if(c_trans_graph[v].pb >= cur_max || c_trans_graph[v].pb > 36500) {
        res.push_back(v);
      }
      for(auto e : c_trans_graph[v].rels) {
        c_trans_graph[e].pb = min(36501, c_trans_graph[e].pb + c_trans_graph[v].pb);
      }
    }
  }
  if(cur_max > 36500) {
    cout<<"zawsze\n";
  } else {
    cout<<cur_max<<"\n";
  }
  for(auto r : res) {
    visited[r] = true;
  }
  res.clear();
  for(int i = 1; i <= n; i++) {
    if(visited[graph[i].scc]) res.push_back(i);
  }

  cout<<res.size()<<"\n";
  for(auto node : res) {
    cout<<node<<" ";
  }

  cout.flush();
}





ll powm(ll a, ll n, ll MOD) {
  ll w = 1;

  while (n > 0) {
    if (n % 2 == 1)
      w = (w * a) % MOD;
      a = (a * a) % MOD;
      n /= 2;
  }
  return w;
}

ll multm(ll a, ll b, ll MOD) {
  return (a * b) % MOD;
}

ll divm(ll a, ll b, ll MOD) {
  return multm(a, powm(b, MOD - 2, MOD), MOD);
}