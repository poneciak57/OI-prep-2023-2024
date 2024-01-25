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

int n;
vec<Node> tree;
vec<int> centroids;
// sub-tree size -> ilosc wierzcholkow w poddrzewie
vec<int> sts;

/**
 * Obliczamy wielkosc poddrzew
 * Jesli rzadne poddrzewo danego wierzcholka nie ma w sobie wiecej niz n/2 wierzcholkow to jest on centroidem
 * Drzewo moze miec 2 centroidy sa zawsze obok siebie
*/
void dfs(int v, int par) {
  sts[v] = 1;
  bool is_centroid = true;
  for(auto w : tree[v].rels) {
    if(w == par) continue;
    dfs(w, v);
    sts[v] += sts[w];
    if(sts[w] > n / 2) is_centroid = false;
  }
  if(n - sts[v] > n / 2) is_centroid = false;
  if(is_centroid) centroids.push_back(v);
}
