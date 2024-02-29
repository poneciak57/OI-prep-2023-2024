#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n;
bool initialized = false;
const int N = 32768;
struct Node { int scc {-1}; vec<int> rels; vec<int> trels; };
vec<Node> default_stree;
vec<Node> seg_tree;
vec<int> values;
vec<pair<int,int>> pairs;
void init();
void prepare_pairs_inp();

void add_rel(int cur, int left, int right, int lOb, int rOb, int node) {
  if(left == lOb && right == rOb) {
    seg_tree[node + N].rels.push_back(cur + 2 * N); // node => !tree
    seg_tree[cur + 2 * N].trels.push_back(node + N);
    seg_tree[cur].rels.push_back(node + 3 * N); // tree => !node
    seg_tree[node + 3 * N].trels.push_back(cur);
    return;
  }

  int mid = (lOb + rOb) / 2;
  if(right <= mid) return add_rel(cur * 2, left, right, lOb, mid, node);
  if(left > mid) return add_rel(cur * 2 + 1, left, right, mid + 1, rOb, node);

  add_rel(cur * 2, left, mid, lOb, mid, node);
  add_rel(cur * 2 + 1, mid + 1, right, mid + 1, rOb, node);
}



void add_to_all(int d) {
  for(int i = 0; i < values.size(); i++) {
    auto lb = lower_bound(values.begin(), values.end(), values[i] + d);
    auto ub = upper_bound(values.begin(), values.end(), values[i] - d);
    if(lb == values.end()) lb--;
    if(*lb >= values[i] + d) lb--;
    if(*ub <= values[i] - d) ub++;

    int left = ub - values.begin(), right = lb - values.begin();
    // !a || !rl
    if(left != i) add_rel(1, left + 1, i - 1 + 1, 1, N, i);
    // !a || !rr
    if(right != i) add_rel(1, i + 1 + 1, right + 1, 1, N, i);
    
  }
}

stack<int> ord;
bitset<4 * N + 7> vis;
void order(int v) {
  if(vis[v]) return;
  vis[v] = true;
  for(auto e : seg_tree[v].rels) order(e);
  ord.push(v);
}
void set_scc(int v, int scc) {
  if(seg_tree[v].scc != -1) return;
  seg_tree[v].scc = scc;
  for(auto e : seg_tree[v].trels) set_scc(e, scc);
}

bool can(int d) {
  init();
  add_to_all(d);
  vis.reset();
  for(int i = 0; i < 4*N; i++) order(i);
  int scc = 0;
  while(!ord.empty()) {
    auto next = ord.top(); ord.pop();
    if(seg_tree[next].scc != -1) continue;
    set_scc(next, scc++); 
  }

  for(int i = 0; i < 2 * N; i++) {
    if(seg_tree[i].scc == seg_tree[i + 2*N].scc) return false;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n;
  prepare_pairs_inp();

  int b = 0, e = 1e9, m;

  while(b + 1 < e) {
    m = (b + e) / 2;
    if(can(m)) b = m;
    else e = m;
  }
  cout<<b;

  cout.flush();
}

void prepare_pairs_inp() {
  vec<vec<int>> flags(n);
  vec<pair<int,int>> tups;
  for(int i = 0; i < n; i++) {
    int a, b;
    cin>>a>>b;
    tups.push_back({a, i});
    tups.push_back({b, i});
  }
  sort(tups.begin(), tups.end());
  for(int i = 0; i < tups.size(); i++) {
    flags[tups[i].second].push_back(i);
    values.push_back(tups[i].first);
  }
  for(int i = 0; i < n; i++) pairs.push_back({flags[i][0], flags[i][1]});
}

void init() {
  if(initialized) {
    seg_tree = default_stree;
    return;
  }
  seg_tree = vec<Node>(4*N);
  for(int i = 2 * N - 1; i > 1; i--) {
    seg_tree[i].rels.push_back(i / 2);
    seg_tree[i / 2].trels.push_back(i);
  }

  for(int i = 1; i < N; i++) {
    seg_tree[i + 2 * N].rels.push_back(i * 2 + 2 * N);
    seg_tree[i + 2 * N].rels.push_back(i * 2 + 1 + 2 * N);
    seg_tree[i * 2 + 2 * N].trels.push_back(i + 2 * N);
    seg_tree[i * 2 + 1 + 2 * N].trels.push_back(i + 2 * N);
  }

  for(auto [a, b] : pairs) {
    seg_tree[a + N].rels.push_back(b + 3 * N);
    seg_tree[b + 3 * N].rels.push_back(a + N);
    seg_tree[a + N].trels.push_back(b + 3 * N);
    seg_tree[b + 3 * N].trels.push_back(a + N);

    seg_tree[b + N].rels.push_back(a + 3 * N);
    seg_tree[a + 3 * N].rels.push_back(b + N);
    seg_tree[b + N].trels.push_back(a + 3 * N);
    seg_tree[a + 3 * N].trels.push_back(b + N);
  }
  default_stree = seg_tree;
  initialized = true;
}