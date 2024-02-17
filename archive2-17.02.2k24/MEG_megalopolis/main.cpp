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

int n, N;

vec<int> seg_tree;
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

void add_on_range(int cur, int left, int right, int lOb, int rOb, int mod) {
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

int get_sum(int c) {
  c += N - 1;
  int sum = 0;
  while(c > 0) {
    sum += seg_tree[c];
    c /= 2;
  }
  return sum;
}

void init();

void print_tree() {
  for(int i = 1; i < 2 * N; i++) {
    cout<<seg_tree[i]<<" ";
  }
  cout<<"\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n;

  tree = vec<Node>(n + 1);
  for(int i = 1; i < n; i++) {
    int a, b;
    cin>>a>>b;
    tree[a].rels.push_back(b);
    tree[b].rels.push_back(a);
  }
  dfs(1, 1, 0);
  init();
  int m, q;
  cin>>m;
  q = n + m - 1;
  while(q--) {
    char op;
    int a, b;
    cin>>op;
    if(op == 'W') {
      cin>>a;
      cout<<tree[a].depth - get_sum(tree[a].pre_order)<<"\n";
    } else {
      cin>>a>>b;
      if(tree[a].depth < tree[b].depth) swap(a, b);
      add_on_range(1, tree[a].from, tree[a].to, 1, N, 1);
      // print_tree();
    }
  }

  cout.flush();
}

void init() {
  N = 1;
  while(N < n) N *= 2;
  seg_tree = vec<int>(2*N, 0);
}