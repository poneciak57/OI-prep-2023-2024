#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

// Dane drzewo
// dwa rodzaje operacji:
// - dodaj wartosc w wierzcholku i wszystkich ponizej
// - wez max na sciezce miedzy danymi wierzcholkami

// 1. Tworzymy zwykle drzewo przedzialowe tak jakbysmy mieli ciag dlugosci n
// 2. Robimy pre processing na ukorzenionym drzewie
//    - parrent
//    - depth
//    - sub tree size
// 3. Obliczamy ciezkie sciezki pre i post order aby obliczyc ciezka sciezke schodzimy od korzenia w dół 
//    do najwiekszych poddrzew a na reszcie tworzymy odnogi rekurencyjnie i ustawiamy path_index
//    dodatkowo ustawiamy post i pre order ale zaczynamy od ciezkiej sciezki z pre orderem
// 4. Robiac modyfikacje w punkcie lub poddrzewie po prostu uzywamy pre i post orderu do wyznaczenia przedzialu
// 5. Pytania o sciezki realizujemy nastepujaco
//    - dopóki indeksy obu sciezek nie sa rowne wybieramy ta ktorej korzen jest najglebiej i wykonujemy operacje na jej przedziale od wierzcholka do korzenia
//    - nastepnie ustawiamy ten wierzcholek na rodzica korzenia przedzialu
//    - jak indeksy sa rowne wykonujemy jeszcze jedno pytanie na drzewie przedzialowym ich pre ordery tworza przedzial

int n, q, N = 1;
struct Vert {
  int par;
  int depth { 0 };
  int stsize { 0 };

  // korzen ciezkiej sciezki
  int path_index;
  int pre_ord;
  int post_ord;

  vec<int> E;
};
struct Node { int max_stree { 0 }; int push_add { 0 }; };
vec<Node> seg_tree;
vec<Vert> graph;
void init() {
  while(N <= n) N *= 2;
  seg_tree = vec<Node>(N * 2);
}
void prop(int cur) {
  if(cur < N) {
    for(int v : {cur * 2, cur * 2 + 1}) {
      seg_tree[v].max_stree += seg_tree[cur].push_add;
      seg_tree[v].push_add += seg_tree[cur].push_add;
    }
    seg_tree[cur].push_add = 0;
  }
}
void updt(int cur) {
  seg_tree[cur].max_stree = max(seg_tree[cur * 2].max_stree, seg_tree[cur * 2 + 1].max_stree);
}
void add(int cur, int left, int right, int lOb, int rOb, int mod) {
  prop(cur);
  if(left == lOb && right == rOb) {
    seg_tree[cur].push_add += mod;
    seg_tree[cur].max_stree += mod;
    return;
  }
  int mid = (lOb + rOb) / 2;
  if(right <= mid) {
    add(cur * 2, left, right, lOb, mid, mod); updt(cur); return;
  }
  if(left > mid) {
    add(cur * 2 + 1, left, right, mid + 1, rOb, mod); updt(cur); return;
  }

  add(cur * 2, left, mid, lOb, mid, mod);
  add(cur * 2 + 1, mid + 1, right, mid + 1, rOb, mod);
  updt(cur);
}
int get_max(int cur, int left, int right, int lOb, int rOb) {
  prop(cur);
  if(left == lOb && right == rOb) {
    return seg_tree[cur].max_stree;
  }
  int mid = (lOb + rOb) / 2;
  if(right <= mid) {
    int ret = get_max(cur * 2, left, right, lOb, mid); updt(cur); return ret;
  }
  if(left > mid) {
    int ret = get_max(cur * 2 + 1, left, right, mid + 1, rOb); updt(cur); return ret;
  }

  int ret = max(get_max(cur * 2, left, mid, lOb, mid), get_max(cur * 2 + 1, mid + 1, right, mid + 1, rOb));
  updt(cur);
  return ret;
}

void dfs_preproc(int v, int p) {
  graph[v].stsize = 1;
  graph[v].par = p;
  for(auto e : graph[v].E) {
    if(e == p) continue;
    graph[e].depth = graph[v].depth + 1;
    dfs_preproc(e, v);
    graph[v].stsize += graph[e].stsize;
  }
}

int pre_tm = 1;

void dfs_hl(int v, int p) {
  graph[v].pre_ord = pre_tm++;
  int max_size = -1;
  int who_max_size = -1;
  for(auto e : graph[v].E) {
    if(e == p) continue;
    if(graph[e].stsize > max_size) {
      max_size = graph[e].stsize;
      who_max_size = e;
    }
  }
  if(who_max_size == -1) {
    graph[v].post_ord = pre_tm - 1;
    return;
  }
  graph[who_max_size].path_index = graph[v].path_index;
  dfs_hl(who_max_size, v);
  for(auto e : graph[v].E) {
    if(e == p || e == who_max_size) continue;
    graph[e].path_index = e;
    dfs_hl(e, v);
  }
  graph[v].post_ord = pre_tm - 1;
}

int get_ans(int x, int y) {
  int ans = -1e7;
  while(graph[x].path_index != graph[y].path_index) {
    // korzen sciezki x jest glebszy niz sciezki y
    if(graph[graph[x].path_index].depth < graph[graph[y].path_index].depth) swap(x, y);
    const int root_x = graph[x].path_index;
    const int max_on_x_path = get_max(1, graph[root_x].pre_ord, graph[x].pre_ord, 1, N);
    ans = max(ans, max_on_x_path);
    x = graph[root_x].par;
  }
  int pre_x = graph[x].pre_ord;
  int pre_y = graph[y].pre_ord;
  if(pre_x > pre_y) swap(pre_x, pre_y);
  const int max_on_path = get_max(1, pre_x, pre_y, 1, N);
  return max(ans, max_on_path);
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n;
  graph = vec<Vert>(n);
  init();
  for(int i = 1, a, b; i < n; i++) {
    cin>>a>>b; --a; --b;
    graph[a].E.push_back(b);
    graph[b].E.push_back(a);
  }

  dfs_preproc(0, -1);
  graph[0].path_index = 0;
  dfs_hl(0, -1);
  // for(int i = 0; i < n; i++) {
  //   cout<<"i: "<<i<<" ";  
  //   cout<<"pind: "<<graph[i].path_index<<" ";
  //   cout<<"pre_ord: "<<graph[i].pre_ord<<" ";
  //   cout<<"post_ord: "<<graph[i].post_ord<<"\n";
  // }
  cin>>q;
  while(q--) {
    str op;
    cin>>op;
    if(op == "add") {
      int v, val;
      cin>>v>>val; --v;
      add(1, graph[v].pre_ord, graph[v].post_ord, 1, N, val);
    } else {
      int x, y;
      cin>>x>>y; --x; --y;
      cout<<get_ans(x, y)<<"\n";
    }
  }
  cout.flush();
}