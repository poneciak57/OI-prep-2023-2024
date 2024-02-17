#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

inline int rand_range(int from, int to) {
  return (rand() % (to - from + 1)) + from;
}

const int N = 1 << 17;
// {max, count}
vec<pair<int,int>> seg_tree;
void init();

void update_up(int node) {
  node /= 2;
  while(node > 0) {
    seg_tree[node].first = max(seg_tree[node * 2].first, seg_tree[node * 2 + 1].first) + seg_tree[node].second;
    node /= 2;
  }
}

void mod_on_range(int cur, int left, int right, int lOb, int rOb, int v) {
  if(left == lOb && right == rOb) {
    seg_tree[cur].first += v;
    seg_tree[cur].second += v;
    return update_up(cur);
  }

  int mid = (lOb + rOb) / 2;
  if(right <= mid) return mod_on_range(cur * 2, left, right, lOb, mid, v);
  if(left > mid) return mod_on_range(cur * 2 + 1, left, right, mid + 1, rOb, v);

  mod_on_range(cur * 2, left, mid, lOb, mid, v);
  mod_on_range(cur * 2 + 1, mid + 1, right, mid + 1, rOb, v);
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  struct Entry {
    int x;
    int y;
    int z;
  };
  vec<Entry> mat;

  int s, w, n;
  cin>>s>>w>>n;
  init();

  for(int i = 0; i < n; i++) {
    int x, y;
    cin>>x>>y;
    mat.push_back({x, y, 1});
    mat.push_back({x, y + w, -1});
  }

  sort(mat.begin(), mat.end(), [](Entry &e1, Entry &e2){ return e1.y < e2.y || (e1.y == e2.y && e1.z > e2.z); });

  int max_v = 0;
  for(auto e : mat) {
    mod_on_range(1, e.x + 30007, e.x + s + 30007, 1, N, e.z);
    max_v = max(max_v, seg_tree[1].first);
  }

  cout<<max_v;
  

  cout.flush();
}

void init() {
  seg_tree = vec<pair<int,int>>(2*N, {0, 0});
}