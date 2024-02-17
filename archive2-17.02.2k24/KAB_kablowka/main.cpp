///
/// SRAM JUZ NA TO ZADANIE IDK CZEMU NIE DZIALA
/// hours wasted: 15

#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Question { int x; int y; ll l; ll r; ll ans{0}; };
struct Node {
  ll from;
  ll to;
  ll k;

  vec<int> rels;

  vec<int> qids;

  int subt_size {1};
  int centroid;
  int centroid_child;
  bool was_centroid {false};
};

int N;
vec<Question> questions;
vec<Node> tree;
// {cur_max, max_down}
vec<pair<ll,ll>> seg_tree;
unordered_map<ll, int> sti;
set<ll> ste;
stack<pair<int,ll>> ops;

void init();
void update_up(int v) {
  if(v >= N) {
    seg_tree[v].second = seg_tree[v].first;
    v /= 2;
  }
  while(v > 0) {
    seg_tree[v].second = max({seg_tree[v].first, seg_tree[v * 2].second, seg_tree[v * 2 + 1].second});
    v /= 2;
  }
}
// ops_count
int update(int cur, int left, int right, int lOb, int rOb, ll val) {
  if(val <= seg_tree[cur].first) return 0;
  if(left == lOb && right == rOb) {
    ll ret = seg_tree[cur].first;
    seg_tree[cur].first = val;
    update_up(cur);
    ops.push({cur, ret});
    return 1;
  }

  int mid = (lOb + rOb) / 2;
  if(right <= mid) return update(cur * 2, left, right, lOb, mid, val);
  if(left > mid) return update(cur * 2 + 1, left, right, mid + 1, rOb, val);

  return update(cur * 2, left, mid, lOb, mid, val) + update(cur * 2 + 1, mid + 1, right, mid + 1, rOb, val);
}
void undo(int count) {
  for(int i = 0; i < count; i++) {
    seg_tree[ops.top().first].first = ops.top().second;
    update_up(ops.top().first);
    ops.pop();
  }
}
ll get_max(int cur, int left, int right, int lOb, int rOb) {
  ll cur_max = seg_tree[cur].first;
  if(left == lOb && right == rOb) return seg_tree[cur].second;
  int mid = (lOb + rOb) / 2;
  if(right <= mid) return max(cur_max, get_max(cur * 2, left, right, lOb, mid));
  if(left > mid) return max(cur_max, get_max(cur * 2 + 1, left, right, mid + 1, rOb));

  ll lside = get_max(cur * 2, left, mid, lOb, mid);
  ll rside = get_max(cur * 2 + 1, mid + 1, right, mid + 1, rOb);
  return max({cur_max, lside, rside});
}

int subt_size(int v, int par) {
  for(auto e : tree[v].rels) {
    if(e == par || tree[e].was_centroid) continue;
    tree[v].subt_size += subt_size(e, v);
  }
  return tree[v].subt_size;
}

int find_centroid(int v, int tsize, int par = -1) {
  for(auto e : tree[v].rels) {
    if(e == par || tree[e].was_centroid) continue;
    if(tree[e].subt_size * 2 > tsize) return find_centroid(e, tsize, v);
  }
  return v;
}

void dfs_set(int v, int centroid, int centroid_child, int par = -1) {
  tree[v].centroid = centroid;
  tree[v].centroid_child = centroid_child;
  for(auto e : tree[v].rels) {
    if(e == par || tree[e].was_centroid) continue;
    dfs_set(e, centroid, centroid_child, v);
  }
}

void answer(int v, int par) {
  auto ops_count = update(1, sti[tree[v].from], sti[tree[v].to], 1, N, tree[v].k);

  for(auto qid : tree[v].qids) {
    auto &q = questions[qid];

    if(tree[q.x].centroid != tree[q.y].centroid) continue;
    else if(tree[q.x].centroid_child == tree[q.y].centroid_child && q.x != tree[q.x].centroid) continue;
    else q.ans = max(q.ans, get_max(1, sti[q.l], sti[q.r], 1, N));
  }

  for(auto e : tree[v].rels) {
    if(e == par || tree[e].was_centroid) continue;
    answer(e, v);
  }

  undo(ops_count);
}

void centroid_decomposition(int v) {
  int tsize = subt_size(v, v);
  int centroid = find_centroid(v, tsize);

  tree[centroid].centroid = centroid;
  tree[centroid].centroid_child = centroid;

  for(auto e : tree[centroid].rels) {
    if(tree[e].was_centroid) continue;
    dfs_set(e, centroid, e, centroid);
  }

  answer(centroid, centroid);

  tree[centroid].was_centroid = true;
  for(auto e : tree[centroid].rels) {
    if(tree[e].was_centroid) continue;
    centroid_decomposition(e);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n, q;
  cin>>n>>q;
  tree = vec<Node>(n + 1);
  questions = vec<Question>(q);
  
  for(int i = 1; i <= n; i++) {
    ll a, b, k;
    cin>>a>>b>>k;
    tree[i].from = a;
    tree[i].to = b;
    tree[i].k = k;
    ste.insert(a);
    ste.insert(b);
  }

  for(int i = 1, a, b; i < n; i++) {
    cin>>a>>b;
    tree[a].rels.push_back(b);
    tree[b].rels.push_back(a);
  }

  for(int i = 0; i < q; i++) {
    int a, b;
    ll l, r;
    cin>>a>>b>>l>>r;
    questions[i] = {a, b, l, r};
    tree[a].qids.push_back(i);
    tree[b].qids.push_back(i);
    if(a == b) tree[b].qids.pop_back();
    ste.insert(l);
    ste.insert(r);
  }

  // for(int i = 1; i <= n; i++) {
  //   cout<<"node #"<<i<<"\n";
  //   cout<<"rels: [ ";
  //   for(auto r : tree[i].rels) cout<<r<<" ";
  //   cout<<"]\n";
  // }

  init();
  centroid_decomposition(1);

  for(auto q : questions) {
    cout<<q.ans<<"\n";
  }
}


void init() {
  int i = 1;
  for(auto e : ste) {
    sti[e] = i++;
  }
  N = 1;
  while(N < i) N *= 2;
  seg_tree = vec<pair<ll, ll>>(N * 2, {0, 0});
}