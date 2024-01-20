#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

ll N, sum = 0;
vec<ll> ceny;
struct Q {
  int from;
  int to;
  ll mod;
};
vec<Q> qs;
set<ll> values;
unordered_map<int, int> ind; // {value, tree_ind}
struct Node {
  ll min;
  int day {INT_MAX};
  ll mod {0};
};
vec<Node> seg_tree;

void init();

void update_up(int v) {
  v /= 2;
  while(v > 0) {
    if(seg_tree[v*2].min <= seg_tree[v*2 + 1].min) {
      seg_tree[v].min = seg_tree[v*2].min + seg_tree[v].mod;
      seg_tree[v].day = seg_tree[v*2].day;
    } else {
      seg_tree[v].min = seg_tree[v*2 + 1].min + seg_tree[v].mod;
      seg_tree[v].day = seg_tree[v*2 + 1].day;
    }
    v /= 2;
  }
}
void update(int cur, int left, int right, int lOb, int rOb, ll mod) {
  if(left == lOb && right == rOb) {
    seg_tree[cur].mod -= mod;
    seg_tree[cur].min -= mod;
    update_up(cur);
    return;
  }

  int mid = (lOb + rOb) / 2;
  if(right <= mid) return update(cur * 2, left, right, lOb, mid, mod);
  if(left > mid) return update(cur * 2 + 1, left, right, mid + 1, rOb, mod);

  update(cur * 2, left, mid, lOb, mid, mod);
  update(cur * 2 + 1, mid + 1, right, mid + 1, rOb, mod);
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n, m;
  cin>>n>>m;
  ceny = vec<ll>(n + 1);
  qs = vec<Q>(m);
  for(int i = 1; i <= n; i++) {
    cin>>ceny[i];
    sum += ceny[i];
  }
  values.insert(1);
  for(int i = 0; i < m; i++) {
    int prod, b, e, nv;
    cin>>prod>>b>>e>>nv;
    values.insert(b);
    values.insert(e);
    qs[i] = {b, e, ceny[prod] - nv};
  }
  
  init();

  // for(auto [k, v] : ind) {
  //   cout<<k<<" -> "<<v<<"\n";
  // }
  // update(1, 1, 3, 1, N, 3);
  // for(int i = 1; i < 2*N; i++) {
  //   cout<<i<<" -> {"<<seg_tree[i].min<<","<<seg_tree[i].day<<","<<seg_tree[i].mod<<"}\n";
  // }
  // return 0;
  for(auto q : qs) {
    update(1, ind[q.from], ind[q.to], 1, N, q.mod);
  }
  cout<<seg_tree[1].min<<" "<<seg_tree[1].day;

  cout.flush();
}


void init() {
  int n = values.size();
  N = 1;
  while(N < n) {
    N *= 2;
  }
  seg_tree = vec<Node>(N*2);
    
  int in = 1;
  for(auto v : values) {
    seg_tree[in - 1 + N].day = v;
    ind[v] = in++;
  }

  for(int i = N; i < 2*N; i++) {
    seg_tree[i].min = sum;
  }
  for(int i = N - 1; i > 0; i--) {
    seg_tree[i] = {sum, min(seg_tree[i *2].day, seg_tree[i * 2 + 1].day)};
  }
}