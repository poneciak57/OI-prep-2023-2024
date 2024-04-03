#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n, N;
const ll INFF = 1e9 + 57;
struct Node {
  ll weight;
  int stsize;
  bool was_centroid { false };
  vec<pair<int,ll>> rels;
};
struct Line {
  ll a, b;
  ll operator()(ll x) { return a * x + b; }
};
vec<ll> ans;
vec<Line> seg_tree;
vec<Node> graph;
// {id, line}
struct Entry {
  int id;
  Line line;
};
int last_line;
vec<Entry> entries;
// set<int> as;
// unordered_map<int, int> emp;
// unordered_map<int, int> imp;
void init(int tsize) {
  N = 1;
  last_line = 0;
  while(N < tsize) N *= 2;
  entries = vec<Entry>(N, {-1, {INFF, INFF}});
  seg_tree = vec<Line>(N * 2, {INFF, INFF});
}
void add(int cur, int left, int right, Line line) {
  int mid = (left + right) / 2;
  int vmid = entries[mid - 1].line.a, vleft = entries[left - 1].line.a, vright = entries[right - 1].line.a;
  if(seg_tree[cur](vmid) > line(vmid)) swap(line, seg_tree[cur]);
  if(left == right) return;
  if(line(vright) < seg_tree[cur](vright)) add(cur * 2 + 1, mid + 1, right, line);
  if(line(vleft) < seg_tree[cur](vleft)) add(cur * 2, left, mid, line);
}
ll get_min(int x, int ind) {
  ll minv = LL_INF;
  int v = ind + N;
  while(v > 0) {
    minv = min(minv, seg_tree[v](x));
    v /= 2;
  }
  return minv;
}

int dfs_stsize(int v, int p) {
  graph[v].stsize = 1;
  for(auto [e, d] : graph[v].rels) {
    if(e == p || graph[e].was_centroid) continue;
    graph[v].stsize += dfs_stsize(e, v);
  }
  return graph[v].stsize;
}

int find_centroid(int v, int tsize, int p) {
  for(auto [e, d] : graph[v].rels) {
    if(e == p || graph[e].was_centroid) continue;
    if(graph[e].stsize * 2 > tsize) return find_centroid(e, tsize, v);
  }
  return v;
}

void dfs(int v, int p, ll dist) {
  entries[last_line] = {v, {graph[v].weight, dist}};
  last_line++;
  for(auto [e, d] : graph[v].rels) {
    if(e == p || graph[e].was_centroid) continue;
    dfs(e, v, dist + d);
  }
}

void centroid_decomp(int v) {
  int tsize = dfs_stsize(v, v);
  int centroid = find_centroid(v, tsize, v);

  init(tsize);
  dfs(centroid, centroid, 0);
  sort(entries.begin(), entries.end(), [](Entry e1, Entry e2) { return e1.line.a < e2.line.a; });
  for(int i = 0 ; i < tsize; i++) add(1, 1, N, entries[i].line);
  for(int i = 0 ; i < tsize; i++) {
    auto [id, line] = entries[i];
    ans[id] = min(ans[id], get_min(line.a, i) + entries[i].line.b);
  }

  graph[centroid].was_centroid = true;
  for(auto [e, d] : graph[centroid].rels) {
    if(graph[e].was_centroid) continue;
    centroid_decomp(e);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>n;
  graph = vec<Node>(n);
  ans = vec<ll>(n, LL_INF);
  for(int i = 0; i < n; i++) {
    int a; cin>>a; graph[i].weight = a;
  }
  for(int i = 1; i < n; i++) {
    int a, b, w;
    cin>>a>>b>>w; --a; --b;
    graph[a].rels.push_back({b, w});
    graph[b].rels.push_back({a, w});
  }

  centroid_decomp(0);

  ll sum = 0; 
  for(int i = 0; i < n; i++) sum += ans[i];
  cout<<sum;

  cout.flush();
}