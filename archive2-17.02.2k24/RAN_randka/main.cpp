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

struct Node {
  int next;
  
  // jesli wierzcholek nalezy do cyklu
  int cid {-1}; // id cyklu
  int cpos {-1}; // pozycja w cyklu

  // jesli wierzcholek nalezy do drzewa
  int depth {-1};

  // typ obiektu 1 - drzewo, 2 - cykl 
  int ot {1};
};  

const int LOG = 20;
int n, k;

// tylko dla drzew, LCA cykli bedzie wypelnione ich id
// [node][log]
vec<vec<int>> LCA;
vec<int> state;
vec<vec<int>> cycles;
vec<Node> graph;
vec<vec<int>> rev_graph;

// zwraca true jesli p1 jest lepsze od p2
// {dziewczyna, chlopak}
bool inline cmp(pair<int,int> p1, pair<int,int> p2) {
  if(max(p1.first, p1.second) < max(p2.first, p2.second)) return true;
  else if(max(p1.first, p1.second) > max(p2.first, p2.second)) return false;

  if(min(p1.first, p1.second) < min(p2.first, p2.second)) return true;
  else if(min(p1.first, p1.second) > min(p2.first, p2.second)) return false;

  return p1.first < p2.first;
}

void init();
void prepare_cycles();
void prepare_lca();
void prepare_depth();

int get_lca(int a, int b) {
  if(graph[a].depth < graph[b].depth) swap(a, b);
  int k = graph[a].depth - graph[b].depth;
  for(int i = LOG - 1; i >= 0; i--) {
    if(k & (1 << i)) a = LCA[a][i];
  }
  if(a == b) return a;

  for(int i = LOG - 1; i >= 0; i--) {
    if(LCA[a][i] != LCA[b][i]) {
      a = LCA[a][i];
      b = LCA[b][i];
    }
  }
  return LCA[a][0];
}


pair<int, int> get_for_cycle(int ch, int d, int chw, int dw) {
  int pch = graph[ch].cpos;
  int pd = graph[d].cpos;

  if(pch >= pd) {
    pair<int, int> p1 = {dw, pd + cycles[graph[ch].cid].size() - pch + chw};
    pair<int, int> p2 = {pch - pd + dw, chw};

    if(cmp(p1, p2)) return p1;
    else return p2;
  } else {
    pair<int, int> p1 = {pch + cycles[graph[d].cid].size() - pd + dw, chw};
    pair<int, int> p2 = {dw, pd - pch + chw};

    if(cmp(p1, p2)) return p1;
    else return p2;
  }  
}

/**
 * Jesli id i typ taki sam i typ == 1 -> LCA
 * Jesli id rozne i typ == 2 -> (-1, -1) jestesmy w roznych cyklach
 * Jesli id rozne i typ == 1 to idziemy do korzenia czyli LCA[LOG] 
 *    jesli id lca sa rozne -> (-1, -1) inny cykl
 *    jesli id lca takie same to kontyuuj jak z cyklami
 * Jesli id i typ taki sam i typ == 2 to dokonujemy sprawdzenia na danym cyklu wg regul
*/

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  init();
  prepare_cycles();
  prepare_lca();
  prepare_depth();

  while(k--) {
    int ch, d;
    cin>>ch>>d;

    // wyniki
    int chw = 0, dw = 0;

    if(graph[ch].ot == graph[d].ot) {
      // typy rowne
      if(graph[ch].ot == 1) {
        // drzewa
        if(LCA[ch][LOG - 1] == LCA[d][LOG - 1]) {
          // to samo drzewo
          int lca = get_lca(ch, d);
          dw = graph[d].depth - graph[lca].depth;
          chw = graph[ch].depth - graph[lca].depth;
          cout<<chw<<" "<<dw<<"\n";
        } else {
          // rozne drzewa
          if(graph[LCA[ch][LOG - 1]].cid == graph[LCA[d][LOG - 1]].cid) {
            // drzewa ida do tego samego cyklu
            chw += graph[ch].depth;
            dw += graph[d].depth;
            // postepowanie jak dla cyklu
            pair<int, int> res = get_for_cycle(LCA[ch][LOG - 1], LCA[d][LOG - 1], chw, dw);
            cout<<res.second<<" "<<res.first<<"\n";
          } else {
            // rozne cykle
            cout<<"-1 -1\n";
          }
        }
      } else {
        // cykle
        if(graph[ch].cid == graph[d].cid) {
          // ten samy cykl
          pair<int, int> res = get_for_cycle(ch, d, 0, 0);
          cout<<res.second<<" "<<res.first<<"\n";
        } else {
          // rozne cykle
          cout<<"-1 -1\n";
        }
      }
    } else {
      // typy rozne
      // dodajemy dla drzewa
      if(graph[ch].ot == 1) {
        chw += graph[ch].depth;
        ch = LCA[ch][LOG - 1];
      } else {
        dw += graph[d].depth;
        d = LCA[d][LOG - 1];
      }

      if(graph[ch].cid == graph[d].cid) {
        // ten samy cykl
        pair<int, int> res = get_for_cycle(ch, d, chw, dw);
        cout<<res.second<<" "<<res.first<<"\n";
      } else {
        // rozne cykle
        cout<<"-1 -1\n";
      }
    }
  }


  cout.flush();
}

void set_depth(int v, int depth) {
  graph[v].depth = depth;

  for(auto e : rev_graph[v]) {
    if(graph[e].ot != 1) continue;
    set_depth(e, depth + 1);
  }
}

void prepare_depth() {
  for(int i = 1; i <= n; i++) {
    if(graph[i].ot == 2) set_depth(i, 0);
  }
}

void prepare_lca() {
  for(int i = 1; i <= n; i++) {
    // jesli cos nalezy do cyklu chcemy aby bylo korzeniem drzewa czyli zawsze prowadzilo do siebie
    if(graph[i].ot == 2) {
      LCA[i][0] = i;
      continue;
    }
    LCA[i][0] = graph[i].next;
  }

  for(int i = 1; i < LOG; i++) {
    for(int j = 1; j <= n; j++) {
      LCA[j][i] = LCA[LCA[j][i - 1]][i - 1];
    }
  }
}

int find_cycle(int v) {
  if(state[v] == 2) return -1;
  if(state[v] == 1) return v;
  state[v] = 1;
  int ret = find_cycle(graph[v].next);
  state[v] = 2;
  return ret;
}

void prepare_cycles() {
  for(int i = 1; i <= n; i++) {
    int v = find_cycle(i);
    if(v == -1) continue;

    vec<int> cycle;
    while(graph[v].ot == 1) {
      graph[v].ot = 2;
      graph[v].cid = cycles.size();
      graph[v].cpos = cycle.size();
      cycle.emplace_back(v);
      v = graph[v].next;
    }
    cycles.emplace_back(cycle);
  }
}

void init() {
  cin>>n>>k;
  graph = vec<Node>(n + 1);
  rev_graph = vec<vec<int>>(n + 1);
  LCA = vec<vec<int>>(n + 1, vec<int>(LOG));
  state = vec<int>(n + 1, 0);
  for(int i = 1, next; i <= n; i++) {
    cin>>next;
    graph[i].next = next;
    rev_graph[next].emplace_back(i);
  }
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