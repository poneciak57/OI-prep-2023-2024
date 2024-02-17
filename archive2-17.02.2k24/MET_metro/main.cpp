#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Node {
  bool visited {false};
  int sasiedzi{0};
  vec<int> rels;
};

vec<Node> tree;

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n, l;
  cin>>n>>l;
  tree = vec<Node>(n + 1);

  for(int i = 1; i < n; i++) {
    int a, b;
    cin>>a>>b;
    tree[a].sasiedzi++;
    tree[b].sasiedzi++;
    tree[a].rels.push_back(b);
    tree[b].rels.push_back(a);
  }

  vec<int> layer;

  for(int i = 1; i <= n; i++) {
    if(tree[i].sasiedzi == 1) {
      layer.push_back(i);
      tree[i].visited = true;
    }
  }

  int sum = 0;
  while(!layer.empty()) {
    vec<int> nlayer;
    sum += min(2*l, (int)layer.size());
    
    for(auto v : layer) {
      for(auto w : tree[v].rels) {
        if(!tree[w].visited) {
          tree[w].sasiedzi--;
          if(tree[w].sasiedzi == 1) {
            nlayer.push_back(w);
            tree[w].visited = true;
          }
        }
      }
    }

    layer = nlayer;
  }

  cout<<sum;


  cout.flush();
}
