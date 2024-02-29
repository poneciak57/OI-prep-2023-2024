#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Node {
  int subt_size {1};
  bool was_centroid {false};
  vec<int> rels;
};
vec<Node> tree;

int count_subt_size(int v, int par) {
  tree[v].subt_size = 1;
  for(auto e : tree[v].rels) {
    if(tree[e].was_centroid || e == par) continue;
    tree[v].subt_size += count_subt_size(e, v);
  }
  return tree[v].subt_size;
}

int find_centroid(int v, int par, int tsize) {
  for(auto e : tree[v].rels) {
    if(e == par || tree[e].was_centroid) continue;

    if(tree[e].subt_size * 2 > tsize) return find_centroid(e, v, tsize); 
  }
  return v;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n;
  cin>>n;
  tree = vec<Node>(n + 1);
  for(int i = 1, a, b; i < n; i++) {
    cin>>a>>b;
    tree[a].rels.push_back(b);
    tree[b].rels.push_back(a);
  }

  int v = 1;
  int tsize = count_subt_size(v, v);
  int c = 0;
  while(tsize > 1) {
    c++;
    int centroid = find_centroid(v, v, tsize);
    tree[centroid].was_centroid = true;
    count_subt_size(centroid, centroid);
    int maxs = 0;
    for(auto e : tree[centroid].rels) {
      if(tree[e].was_centroid) continue;
      if(tree[e].subt_size > maxs) {
        maxs = tree[e].subt_size;
        v = e;
      }
    }
    tsize = count_subt_size(v, v);
  }
  cout<<c;

  cout.flush();
}