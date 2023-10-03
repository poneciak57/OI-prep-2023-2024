#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

struct Node {
  ll pre_order { 0 };
  ll post_order { 0 };

  vec<ll> rels;
};

vec<Node> graf;
vec<bool> visited;

ll post { 0 };
ll pre { 0 };

void dfs (ll n) {
  graf[n].pre_order = pre;
  pre++;
  visited[n] = true;
  for (ll r : graf[n].rels) {
    if(!visited[r]) {
      dfs(r);
    }
  }
  graf[n].post_order = post;
  post++;
}