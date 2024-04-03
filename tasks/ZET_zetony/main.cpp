#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int t, n, m, N;

vec<int> seg_tree;
void init() {
  N = 1;
  while(N <= n) N *= 2;
  seg_tree = vec<int>(2 * N, 0);
}
void inc(int v) {
  v += N;
  while(v > 0) {
    seg_tree[v]++;
    v /= 2;
  }
}
int sum(int cur, int left, int right, int lOb, int rOb) {
  if(left == lOb && right == rOb) return seg_tree[cur];
  int mid = (lOb + rOb) / 2;
  if(right <= mid) return sum(cur * 2, left, right, lOb, mid);
  if(left > mid) return sum(cur * 2 + 1, left, right, mid + 1, rOb);
  return sum(cur * 2, left, mid, lOb, mid) + sum(cur * 2 + 1, mid + 1, right, mid + 1, rOb);
}

struct Node {
  int depth { 0 };
  int parent;
  int stsize { 1 };

  int path_id;
  int pre_ord;
  int post_ord;

  vec<int> rels;
};
vec<Node> graph;

void dfs_preproc(int v, int p) {
  graph[v].parent = p;
  graph[v].depth = graph[p].depth + 1;
  for(auto e : graph[v].rels) {
    if(e == p) continue;
    dfs_preproc(e, v);
    graph[v].stsize += graph[e].stsize;
  }
}

int pre_tm = 1;
void dfs_hl(int v, int p) {
  graph[v].pre_ord = pre_tm++;
  int max_size = -1;
  int who_max_size = -1;
  for(auto e : graph[v].rels) {
    if(e == p) continue;
    if(graph[e].stsize > max_size) {
      max_size = graph[e].stsize;
      who_max_size = e;
    }
  }

  if(who_max_size != -1) {
    graph[who_max_size].path_id = graph[v].path_id;
    dfs_hl(who_max_size, v);
    for(auto e : graph[v].rels) {
      if(e == p || e == who_max_size) continue;
      graph[e].path_id = e;
      dfs_hl(e, v);
    }
  }
  graph[v].post_ord = pre_tm - 1;
}



int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>t;
  while(t--) {
    cin>>n;
    graph = vec<Node>(n);
    for(int i = 0, u, v; i < n; i++) {
      cin>>u>>v; --u; --v;
      graph[u].rels.push_back(v);
      graph[v].rels.push_back(u);
    }
    dfs_preproc(0, 0);
    graph[0].path_id = 0;
    dfs_hl(0, 0);
  }
  

  cout.flush();
}