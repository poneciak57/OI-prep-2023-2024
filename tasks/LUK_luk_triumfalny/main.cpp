#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Node {
  bool v{false};
  vec<int> rels;
};

vec<Node> tree;

int check(int node, int k, int parrent) {
  int sum = 0;
  for(auto child : tree[node].rels) {
    if(child != parrent) {
      sum += check(child, k, node) + 1;
    }
  }
  return max(0, sum - k);
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n;
  cin>>n;
  tree = vec<Node>(n + 1);

  for(int i = 1; i < n; i++) {
    int f, t;
    cin>>f>>t;
    tree[f].rels.push_back(t);
    tree[t].rels.push_back(f);
  }

  int b = -1, e = 300000, m;
  while(b + 1 < e) {
    m = (b + e)/2;
    if(check(1, m, 1) == 0) {
      e = m;
    } else {
      b = m;
    }
  }
  cout<<e;

  cout.flush();
}
