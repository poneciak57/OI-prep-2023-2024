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

  int subt_size {1};
  int centroid;
  int centroid_child;
  bool was_centroid {false};
};

vec<Node> tree;

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

void centroid_decomposition(int v) {
  int tsize = subt_size(v, v);
  int centroid = find_centroid(v, tsize);

  tree[centroid].centroid = centroid;
  tree[centroid].centroid_child = centroid;

  for(auto e : tree[centroid].rels) {
    if(tree[e].was_centroid) continue;
    dfs_set(e, centroid, e, centroid);
  }

  // odpowiadamy na zapytania albo wykonujemy jakas czynnosc

  tree[centroid].was_centroid = true;
  for(auto e : tree[centroid].rels) {
    if(tree[e].was_centroid) continue;
    centroid_decomposition(e);
  }
}