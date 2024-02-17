#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Node {
  int pre_order;
  int from;
  int to;
  int depth;
  int parrent;

  vec<int> rels;
};

const int LOG = 20;
int n, N, q;

vec<ll> seg_tree;
vec<vec<int>> lca;
vec<Node> tree;

int pre = 0;
void dfs(int v, int par, int depth) {
  pre++;
  tree[v].parrent = par;
  tree[v].depth = depth;
  tree[v].pre_order = pre;
  tree[v].from = pre;

  for(auto e : tree[v].rels) {
    if(e == par) continue;
    dfs(e, v, depth + 1);
  }

  tree[v].to = pre;
}

void add_on_range(int cur, int left, int right, int lOb, int rOb, ll mod) {
  if(left == lOb && right == rOb) {
    seg_tree[cur] += mod;
    return;
  }
  int mid = (lOb + rOb) / 2;
  if(right <= mid) return add_on_range(cur * 2, left, right, lOb, mid, mod);
  if(left > mid) return add_on_range(cur * 2 + 1, left, right, mid + 1, rOb, mod);

  add_on_range(cur * 2, left, mid, lOb, mid, mod);
  add_on_range(cur * 2 + 1, mid + 1, right, mid + 1, rOb, mod);
}

int get_lca(int a, int b) {
  if(tree[a].depth < tree[b].depth) swap(a, b);
  int k = tree[a].depth - tree[b].depth;
  for(int i = LOG - 1; i >= 0; i--) {
    if(k & (1 << i)) a = lca[i][a];
  }
  if(a == b) return a;
  
  for(int i = LOG - 1; i >= 0; i--) {
    if(lca[i][a] != lca[i][b]) {
      a = lca[i][a];
      b = lca[i][b];
    }
  }
  return lca[0][a];
}

ll get_sum(int c) {
  c += N - 1;
  ll sum = 0;
  while(c > 0) {
    sum += seg_tree[c];
    c /= 2;
  }
  return sum;
}

void init();

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n>>q;

  tree = vec<Node>(n + 1);
  // 1 - pytanie, 2 - sciezka
  struct Entry { int type; int from; int to; ll x; ll y; int qid; };
  vec<Entry> entries;
  vec<ll> questions;
  for(int i = 1; i < n; i++) {
    ll a, b, x, y;
    cin>>a>>b>>x>>y;
    tree[a].rels.push_back(b);
    tree[b].rels.push_back(a);
    entries.push_back({2, (int)a, (int)b, x, y, -1});
  }
  dfs(1, 1, 0);
  init();
  while(q--) {
    int a, b; ll k;
    cin>>a>>b>>k;
    questions.push_back(0);
    entries.push_back({1, a, b, k, -1, (int)(questions.size() - 1)});
  }
  
  sort(entries.begin(), entries.end(), [](Entry &e1, Entry &e2) { return e1.x < e2.x || (e1.x == e2.x && e1.type > e2.type); });

  for(auto [type, from, to, x, y, qid] : entries) {
    if(tree[from].depth < tree[to].depth) swap(from, to);
    if(type == 2) add_on_range(1, tree[from].from, tree[from].to, 1, N, y);
    else questions[qid] = get_sum(tree[from].pre_order) + get_sum(tree[to].pre_order) - 2 * get_sum(tree[get_lca(from, to)].pre_order);
  }

  for(auto qe : questions) {
    cout<<qe<<"\n";
  }

  cout.flush();
}

void init() {
  N = 1;
  while(N < n) N *= 2;
  seg_tree = vec<ll>(2*N, 0);

  lca = vec<vec<int>>(LOG, vec<int>(n + 1));
  for(int i = 1; i <= n; i++) lca[0][i] = tree[i].parrent;

  for(int i = 1; i < LOG; i++) {
    for(int j = 1; j <= n; j++) lca[i][j] = lca[i - 1][lca[i - 1][j]];
  }
}