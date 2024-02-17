#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const int LOG = 19;

struct Node {
  int top_node;
  int depth;
  vec<int> childs;
  int up[LOG];
};

vec<Node> tree;
set<int> waiting;

void dfs(int node, int parrent, int depth, int top_node) {
  tree[node].depth = depth;
  tree[node].top_node = top_node;
  tree[node].up[0] = parrent;
  
  for(int i = 1; i < LOG; i++) {
    tree[node].up[i] = tree[tree[node].up[i - 1]].up[i - 1];
  }
  for(auto child : tree[node].childs) {
    dfs(child, node, depth + 1, top_node);
  }
}

int find_top(int node, int new_top) {
  int prev = node;
  while(node != tree[node].top_node) {
    node = tree[node].top_node;
    tree[prev].top_node = new_top;
    prev = node;
  }
  tree[prev].top_node = new_top;
  return node;
}

void recalculate() {
  if(waiting.empty()) return;

  for(auto sv : waiting) {
    dfs(sv, sv, 0, sv);
  }
  waiting.clear();
}

int get_dist(int a, int b) {
  if(tree[a].top_node != tree[b].top_node) return -1;
  if(tree[a].depth < tree[b].depth) swap(a, b);
  int dist = tree[a].depth - tree[b].depth;

  for(int i = LOG - 1; i >= 0; i--) {
    if(dist & (1 << i)) a = tree[a].up[i];
  }

  if(a == b) return dist;
  for(int i = LOG - 1; i >= 0; i--) {
    if(tree[a].up[i] != tree[b].up[i]) {
      a = tree[a].up[i];
      b = tree[b].up[i];
      dist += 2 * (1 << i);
    }
  }

  return dist + 2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n, m;
  cin>>n>>m;
  tree = vec<Node>(n + 1);
  for(int i = 1; i <= n; i++) {
    tree[i].top_node = i;
    tree[i].depth = 0;
  }

  while(m--) {
    int a, b, c;
    cin>>a>>b>>c;
    if(a == 1) {
      int new_id = tree.size();
      int b_top = find_top(b, new_id);
      int c_top = find_top(c, new_id);
      if(b == c) tree.push_back({new_id, 0, {b_top}});
      else tree.push_back({new_id, 0, {b_top, c_top}});

      waiting.erase(b_top);
      waiting.erase(c_top);
      waiting.insert(new_id);
    } else {
      recalculate();
      cout<<get_dist(b, c)<<"\n";
    }
  }

  cout.flush();
}
