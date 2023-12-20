#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Node {
  vec<int> rels;
};

vec<Node> tree;
vec<int> has_dynamite;

const int MAX_LK_DIST = 300007;
int knot_count;
pair<int,int> get_down(int node, int k, int parrent) {
  int LD_dist = has_dynamite[node] - 1;
  int LK_dist = MAX_LK_DIST;
  for(auto rel : tree[node].rels) {
    if(rel != parrent) {
      auto [rel_LDmax, rel_LKmin] = get_down(rel, k, node);
      LD_dist = max(LD_dist, rel_LDmax);
      LK_dist = min(LK_dist, rel_LKmin);
    }
  }

  if(LD_dist + LK_dist <= k) {
    LD_dist = -1;
  } else if(LD_dist >= k) {
    knot_count++;
    LD_dist = -1;
    LK_dist = 0;
  }
  if(LD_dist != -1) {
    LD_dist++;
  }
  return {LD_dist, min(LK_dist + 1, MAX_LK_DIST)};
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n, k;
  cin>>n>>k;
  tree = vec<Node>(n + 1);
  has_dynamite = vec<int>(n + 1);
  for(int i = 1; i <= n; i++) {
    cin>>has_dynamite[i];
  }

  for(int i = 1; i < n; i++) {
    int a, b;
    cin>>a>>b;
    tree[a].rels.push_back(b);
    tree[b].rels.push_back(a);
  }


  int b = -1, e = n, m;
  while(b + 1 < e) {
    m = (b + e) / 2;
    knot_count = 0;
    auto [LDmax, LKmin] = get_down(1, m, -1);
    if((LDmax >= m) && !(LDmax + LKmin <= m)) knot_count++;

    if(knot_count <= k) {
      e = m;
    } else {
      b = m;
    }
  }
  cout << e;

  cout.flush();
}
