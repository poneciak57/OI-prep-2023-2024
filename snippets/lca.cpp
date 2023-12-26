#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

// max_depth = 1048576
const int LOG = 20;
const int MAX_N = 1000000;

vec<int> children[MAX_N];
int up[MAX_N][LOG]; // up[v][j] is 2^j-th ancestor of v
int depth[MAX_N];

// O(n*log_n)
void dfs(int v) {
  for(int child : children[v]) {
    up[child][0] = v;
    depth[child] = depth[v] + 1;
    for(int j = 1; j < LOG; j++) {
      up[child][j] = up[up[child][j - 1]][j - 1];
    }
    dfs(child);
  }
}

// O(n)
int get_lca_brut(int a, int b) {
  if(depth[a] < depth[b]) swap(a, b);
  while(depth[a] > depth[b]) a = up[a][0];

  while (a != b) {
    a = up[a][0];
    b = up[b][0];
  }
  return a;
}

int get_lca_optimal(int a, int b) {
  if(depth[a] < depth[b]) swap(a, b);

  int k = depth[a] - depth[b];
  for(int j = LOG - 1; j >= 0; j--) {
    if(k & (1 << j)) a = up[a][j];
  }
  if(a == b) return a; // if one of a or b is ancestor of another

  for(int j = LOG - 1; j >= 0; j--) {
    if(up[a][j] != up[b][j]) {
      a = up[a][j];
      b = up[b][j];
    }
  }
  return up[a][0];
}


int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  
  cout.flush();
}
